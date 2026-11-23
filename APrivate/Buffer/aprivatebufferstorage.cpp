// ----------------------------------------------------------
/*!
	\class APrivateBufferStorage
	\title
	\brief Locked, non-dumpable, guarded storage for secret data
	(keys, passwords, plaintext) built on the OpenSSL secure heap.

	Primary storage is the OpenSSL secure heap (CRYPTO_secure_*):
	a single mmap()'ed arena surrounded by PROT_NONE guard pages,
	mlock()'ed, excluded from core dumps (where the OS allows) and
	cleansed with OPENSSL_cleanse() on every free.

	If the secure heap was not initialised (see mSecureHeapInit())
	or is exhausted, a private mmap() region with the same properties
	(guard pages, mlock, no-dump, wipe-on-fork where supported) is used,
	and it is wiped with OPENSSL_cleanse() as well.

	Platforms: iOS, Android, macOS (any POSIX target OpenSSL is built for
	without "no-secure-memory").

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/11/2026 at 20:20:19
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "aprivatebufferstorage.h"

// Constant and efinitions
#if !defined(MAP_ANONYMOUS) && defined(MAP_ANON)
# define MAP_ANONYMOUS MAP_ANON
#endif

// Namespace
namespace ARB {

// Static members
std::mutex APrivateBufferStorage::pHeapMutex;
std::atomic<int> APrivateBufferStorage::pHeapState{int(APrivateBufferStorage::APrivateBufferStorageHeapState::Failed)};


// -----------
/*!
	\fn size_t APrivateBufferStorage::mPageSize(void) noexcept

	Returns the system memory page size (16 KiB on Apple Silicon / iOS,
	4 KiB or 16 KiB on Android).
*/

size_t APrivateBufferStorage::mPageSize(void) noexcept {

	static const size_t oPageSize = [] {
		const long oValue = sysconf(_SC_PAGESIZE);
		return oValue > 0 ? size_t(oValue) : size_t(16384);
	}();
	return oPageSize;
}


// -----------
/*!
	\fn APrivateBufferStorage::APrivateBufferStorage(qsizetype inCapacity)

	Allocates zero-filled storage of at least \a inCapacity bytes.
	Throws std::bad_alloc (qBadAlloc()) on failure.
*/

APrivateBufferStorage::APrivateBufferStorage(qsizetype inCapacity) {

	if (inCapacity <= 0) return;

	const size_t oCapacity = size_t(inCapacity);

	if (mHeapState() != APrivateBufferStorageHeapState::Failed) {
		void* oPointer = CRYPTO_secure_zalloc(oCapacity,OPENSSL_FILE,OPENSSL_LINE);
		if (oPointer && CRYPTO_secure_allocated(oPointer)) {
			pPointer = static_cast<char*>(oPointer);
			pAllocated = CRYPTO_secure_actual_size(oPointer);
			if (pAllocated < oCapacity) pAllocated = oCapacity;
			OPENSSL_cleanse(pPointer,pAllocated);
			pHeap = true;
			pMemoryLocked = mHeapState() == APrivateBufferStorageHeapState::Locked;
			return;
		}

		if (oPointer) CRYPTO_clear_free(oPointer,oCapacity,OPENSSL_FILE,OPENSSL_LINE);
	}

	mAllocateFallback(oCapacity);
}


// -----------
/*!
	\fn APrivateBufferStorage::~APrivateBufferStorage(void)

	Cleanses the whole storage and releases it.
*/

APrivateBufferStorage::~APrivateBufferStorage(void) {

	if (!pPointer) return;

	if (pHeap) {
		CRYPTO_secure_clear_free(pPointer,pAllocated,OPENSSL_FILE,OPENSSL_LINE);
	} else {
		mReleaseFallback();
	}

	pPointer = nullptr;
	pAllocated = 0;
	pSize = 0;
}


// -----------
/*!
	\fn void APrivateBufferStorage::mAllocateFallback(size_t inCapacity)

	Private anonymous mapping: [guard page][data pages][guard page].
*/

void APrivateBufferStorage::mAllocateFallback(size_t inCapacity) {

	const size_t oPageSize = mPageSize();

	constexpr size_t oMaxQSize = size_t(std::numeric_limits<qsizetype>::max());
	if (oMaxQSize < 3 * oPageSize || inCapacity > oMaxQSize - 3 * oPageSize) qBadAlloc();

	const size_t oAllocated = (inCapacity + oPageSize - 1) / oPageSize * oPageSize;
	const size_t oMapped = oAllocated + 2 * oPageSize;

	void* oBase = mmap(nullptr,oMapped,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
	if (oBase == MAP_FAILED) qBadAlloc();

	char* oBytes = static_cast<char*>(oBase);
	if (mprotect(oBytes,oPageSize,PROT_NONE) != 0
		|| mprotect(oBytes + oPageSize + oAllocated,oPageSize,PROT_NONE) != 0) {
		munmap(oBase,oMapped);
		qBadAlloc();
	}

	pPointer = oBytes + oPageSize;
	pAllocated = oAllocated;

#if defined(MADV_DONTDUMP)
	madvise(pPointer,pAllocated,MADV_DONTDUMP);
#elif defined(MADV_NOCORE)
	madvise(pPointer,pAllocated,MADV_NOCORE);
#endif

#if defined(MADV_WIPEONFORK)
	madvise(pPointer,pAllocated,MADV_WIPEONFORK);
#endif

	pMemoryLocked = mlock(pPointer,pAllocated) == 0;
}


// -----------
/*!
	\fn void APrivateBufferStorage::mReleaseFallback(void) noexcept

	Cleanses, unlocks and unmaps the fallback mapping including guard pages.
*/

void APrivateBufferStorage::mReleaseFallback(void) noexcept {

	const size_t oPageSize = mPageSize();

	OPENSSL_cleanse(pPointer,pAllocated);
	if (pMemoryLocked) munlock(pPointer,pAllocated);
	munmap(pPointer - oPageSize,pAllocated + 2 * oPageSize);
	pMemoryLocked = false;
}


// -----------
/*!
	\fn char* APrivateBufferStorage::mData(void) noexcept
*/

char* APrivateBufferStorage::mData(void) noexcept {

	return pPointer;
}


// -----------
/*!
	\fn const char* APrivateBufferStorage::mConstData(void) const noexcept
*/

const char* APrivateBufferStorage::mConstData(void) const noexcept {

	return pPointer;
}


// -----------
/*!
	\fn qsizetype APrivateBufferStorage::mSize(void) const noexcept
*/

qsizetype APrivateBufferStorage::mSize(void) const noexcept {

	return pSize;
}


// -----------
/*!
	\fn void APrivateBufferStorage::mSizeSet(qsizetype inSize) noexcept

	Sets the used size. When shrinking, the released tail is cleansed.
	Out-of-range values are clamped to [0, capacity].
*/

void APrivateBufferStorage::mSizeSet(qsizetype inSize) noexcept {

	Q_ASSERT(inSize >= 0 && size_t(inSize) <= pAllocated);

	if (inSize < 0) inSize = 0;
	if (size_t(inSize) > pAllocated) inSize = qsizetype(pAllocated);

	if (inSize < pSize) OPENSSL_cleanse(pPointer + inSize,size_t(pSize - inSize));
	pSize = inSize;
}


// -----------
/*!
	\fn size_t APrivateBufferStorage::mCapacity(void) const noexcept
*/

size_t APrivateBufferStorage::mCapacity(void) const noexcept {

	return pAllocated;
}


// -----------
/*!
	\fn bool APrivateBufferStorage::mIsLocked(void) const noexcept

	True if the storage is pinned in RAM (cannot be swapped out).
*/

bool APrivateBufferStorage::mIsLocked(void) const noexcept {

	return pMemoryLocked;
}


// -----------
/*!
	\fn bool APrivateBufferStorage::mIsSecureHeap(void) const noexcept

	True if the storage lives in the OpenSSL secure heap.
*/

bool APrivateBufferStorage::mIsHeap(void) const noexcept {

	return pHeap;
}


// -----------
/*!
	\fn void APrivateBufferStorage::mWipe(void) noexcept

	Cleanses the whole storage and resets the size.
*/

void APrivateBufferStorage::mWipe(void) noexcept {

	mZeroing(pPointer,pAllocated);
	pSize = 0;
}


// -----------
/*!
	\fn bool APrivateBufferStorage::mIsEqual(const void* inData,qsizetype inSize) const noexcept

	Constant-time comparison of the stored data with \a inData.
	Only the length is leaked through timing.
*/

bool APrivateBufferStorage::mIsEqual(const void* inData,qsizetype inSize) const noexcept {

	if (inSize != pSize) return false;
	if (pSize == 0) return true;
	if (!inData || !pPointer) return false;
	return mConstTimeEqual(pPointer,inData,size_t(pSize));
}


// -----------
/*!
	\fn bool APrivateBufferStorage::mIsEqual(const APrivateBufferStorage& inOther) const noexcept
*/

bool APrivateBufferStorage::mIsEqual(const APrivateBufferStorage& inOther) const noexcept {

	return mIsEqual(inOther.mConstData(),inOther.mSize());
}


// -----------
/*!
	\fn void APrivateBufferStorage::mZeroing(void* inPointer,size_t inSize) noexcept

	Zeroes memory in a way the compiler cannot optimise away.
*/

void APrivateBufferStorage::mZeroing(void* inPointer,size_t inSize) noexcept {

	if (!inPointer || !inSize) return;
	OPENSSL_cleanse(inPointer,inSize);
}


// -----------
/*!
	\fn bool APrivateBufferStorage::mConstTimeEqual(const void* inA,const void* inB,size_t inSize) noexcept

	Constant-time memory comparison (CRYPTO_memcmp).
*/

bool APrivateBufferStorage::mConstTimeEqual(const void* inA,const void* inB,size_t inSize) noexcept {

	if (!inSize) return true;
	if (!inA || !inB) return false;
	return CRYPTO_memcmp(inA,inB,inSize) == 0;
}


// -----------
/*!
	\fn APrivateBufferStorage::SecureHeapState APrivateBufferStorage::mSecureHeapInit(size_t inHeapSize,size_t inMinSize) noexcept

	Initialises the process-wide OpenSSL secure heap. Call once at startup.
	Size the heap to fit RLIMIT_MEMLOCK: on Android it is usually 64 KiB,
	so the default of 32 KiB is safe; on macOS a larger value is fine.
	Returns the resulting state; repeated calls return the current state.
*/

APrivateBufferStorage::APrivateBufferStorageHeapState APrivateBufferStorage::mHeapInit(
	size_t inHeapSize,size_t inMinSize) noexcept {

	std::lock_guard<std::mutex> oLock(pHeapMutex);

	if (CRYPTO_secure_malloc_initialized()) {
		return APrivateBufferStorageHeapState(pHeapState.load(std::memory_order_acquire));
	}
	// Secure-heap blocks can be as large as the heap; keep them qsizetype-safe too
	if (inHeapSize > size_t(std::numeric_limits<qsizetype>::max())) {
		return APrivateBufferStorageHeapState::Failed;
	}
	if (!mIsPowerOfTwo(inHeapSize) || !mIsPowerOfTwo(inMinSize) || inMinSize >= inHeapSize) {
		return APrivateBufferStorageHeapState::Failed;
	}

	int oResult = CRYPTO_secure_malloc_init(inHeapSize,inMinSize);
	if (oResult != 1 && oResult != 2) oResult = 0;
	pHeapState.store(oResult,std::memory_order_release);
	return APrivateBufferStorageHeapState(oResult);
}


// -----------
/*!
	\fn APrivateBufferStorage::SecureHeapState APrivateBufferStorage::mSecureHeapState(void) noexcept
*/

APrivateBufferStorage::APrivateBufferStorageHeapState APrivateBufferStorage::mHeapState(void) noexcept {

	const int oState = pHeapState.load(std::memory_order_acquire);
	if (oState != int(APrivateBufferStorageHeapState::Failed)) return APrivateBufferStorageHeapState(oState);

	// Heap initialised elsewhere (directly via OpenSSL): usable,
	// but lock status unknown -> report conservatively as not locked
	return CRYPTO_secure_malloc_initialized()
		? APrivateBufferStorageHeapState::NotLocked
		: APrivateBufferStorageHeapState::Failed;
}


// -----------
/*!
	\fn size_t APrivateBufferStorage::mSecureHeapUsed(void) noexcept

	Bytes currently allocated from the secure heap.
*/

size_t APrivateBufferStorage::mHeapUsed(void) noexcept {

	// CRYPTO_secure_used() dereferences a NULL lock when the heap
	// is not initialised (OpenSSL 3.0.x) - guard it
	std::lock_guard<std::mutex> oLock(pHeapMutex);
	return CRYPTO_secure_malloc_initialized() ? CRYPTO_secure_used() : 0;
}


// -----------
/*!
	\fn bool APrivateBufferStorage::mSecureHeapDone(void) noexcept

	Releases the secure heap. Fails (returns false) while any
	secure-heap backed APrivateBufferStorage still exists.
*/

bool APrivateBufferStorage::mHeapDone(void) noexcept {

	std::lock_guard<std::mutex> oLock(pHeapMutex);

	if (!CRYPTO_secure_malloc_initialized()) return true;
	if (CRYPTO_secure_malloc_done() != 1) return false;
	pHeapState.store(int(APrivateBufferStorageHeapState::Failed),std::memory_order_release);
	return true;
}


// -----------
/*!
	\fn bool APrivateBufferStorage::mIsPowerOfTwo(size_t inValue) noexcept

	Private: true if \a inValue is a non-zero power of two.
*/

bool APrivateBufferStorage::mIsPowerOfTwo(size_t inValue) noexcept {

	return inValue && !(inValue & (inValue - 1));
}

} // namespace ARB
