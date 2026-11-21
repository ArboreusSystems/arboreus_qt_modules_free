// ----------------------------------------------------------
/*!
	\class APrivateBufferStorage
	\title
	\brief Template file files/cppheader/file.h

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

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

size_t fPrivateBufferStorage_PageSize(void) noexcept {

	const long oPageSize = sysconf(_SC_PAGESIZE);
	return oPageSize > 0 ? size_t(oPageSize) : 16384;
}


// -----------
/*!
	\fn

	Doc.
*/

APrivateBufferStorage::APrivateBufferStorage(qsizetype inCapacity) {

	if (inCapacity <= 0) return;

	const size_t oPageSize = fPrivateBufferStorage_PageSize();
	if (size_t(inCapacity) > std::numeric_limits<size_t>::max() - oPageSize) qBadAlloc();
	pAllocated = (size_t(inCapacity) + oPageSize - 1) / oPageSize * oPageSize;

	void* oPointer = mmap(nullptr,pAllocated,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
	if (oPointer == MAP_FAILED) qBadAlloc();
	pPointer = static_cast<char*>(oPointer);

#if defined(MADV_DONTDUMP)
	madvise(pPointer,pAllocated,MADV_DONTDUMP);
#elif defined(MADV_NOCORE)
	madvise(pPointer,pAllocated,MADV_NOCORE);
#endif

	pMemoryLocked = mlock(pPointer,pAllocated) == 0;
}


// -----------
/*!
	\fn

	Doc.
*/

APrivateBufferStorage::~APrivateBufferStorage(void) {

	if (!pPointer) return;
	mZeroing(pPointer, pAllocated);

	if (pMemoryLocked) munlock(pPointer, pAllocated);
	munmap(pPointer, pAllocated);
}


// -----------
/*!
	\fn

	Doc.
*/

char* APrivateBufferStorage::mData(void) noexcept {

	return pPointer;
}


// -----------
/*!
	\fn

	Doc.
*/

const char* APrivateBufferStorage::mConstData(void) const noexcept {

	return pPointer;
}


// -----------
/*!
	\fn

	Doc.
*/

qsizetype APrivateBufferStorage::mSize(void) const noexcept {

	return pSize;
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivateBufferStorage::mSizeSet(qsizetype inSize) noexcept {

	Q_ASSERT(inSize >= 0 && size_t(inSize) <= pAllocated);
	pSize = inSize;
}


// -----------
/*!
	\fn

	Doc.
*/

size_t APrivateBufferStorage::mCapacity(void) const noexcept {

	return pAllocated;
}


// -----------
/*!
	\fn

	Doc.
*/

bool APrivateBufferStorage::mIsLocked(void) const noexcept {

	return pMemoryLocked;
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivateBufferStorage::mWipe(void) noexcept {

	mZeroing(pPointer,pAllocated);
	pSize = 0;
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivateBufferStorage::mZeroing(void* inPointer,size_t inSize) noexcept {

	if (!inPointer || !inSize) return;

#if defined(Q_OS_DARWIN)
	memset_s(inPointer,inSize,0,inSize);
#else
	volatile unsigned char* oVolatile = static_cast<volatile unsigned char*>(inPointer);
	while (inSize--) *oVolatile++ = 0;
#endif
}
