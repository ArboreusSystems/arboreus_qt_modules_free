// ----------------------------------------------------------
/*!
	\headerfile APrivateBufferStorage
	\title
	\brief Locked, non-dumpable, guarded storage for secret data
	(keys, passwords, plaintext) built on the OpenSSL secure heap.

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/11/2026 at 20:20:19
	\endlist
*/
// ----------------------------------------------------------

#ifndef APRIVATEBUFFERSTORAGE_H
#define APRIVATEBUFFERSTORAGE_H

// Precompiled includes
#include <aprivate_pch.h>

// System includes

// Application includes

// Namesapces

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class APrivateBufferStorage {

	public:

		enum class APrivateBufferStorageHeapState : int {

			Failed = 0,
			Locked = 1,
			NotLocked = 2
		};

		explicit APrivateBufferStorage(qsizetype inCapacity);
		~APrivateBufferStorage(void);

		Q_DISABLE_COPY_MOVE(APrivateBufferStorage)

		char* mData(void) noexcept;
		const char* mConstData(void) const noexcept;
		qsizetype mSize(void) const noexcept;
		void mSizeSet(qsizetype inSize) noexcept;
		size_t mCapacity(void) const noexcept;
		bool mIsLocked(void) const noexcept;
		bool mIsHeap(void) const noexcept;
		void mWipe(void) noexcept;
		bool mIsEqual(const void* inData,qsizetype inSize) const noexcept;
		bool mIsEqual(const APrivateBufferStorage& inOther) const noexcept;

		static void mZeroing(void* inPointer,size_t inSize) noexcept;
		static bool mConstTimeEqual(const void* inA,const void* inB,size_t inSize) noexcept;
		static size_t mPageSize(void) noexcept;
		static APrivateBufferStorageHeapState mHeapInit(size_t inHeapSize = 32768,size_t inMinSize = 16) noexcept;
		static APrivateBufferStorageHeapState mHeapState(void) noexcept;
		static size_t mHeapUsed(void) noexcept;
		static bool mHeapDone(void) noexcept;

	private:

		char* pPointer = nullptr;
		size_t pAllocated = 0;
		qsizetype pSize = 0;
		bool pMemoryLocked = false;
		bool pHeap = false;
		static std::mutex pHeapMutex;
		static std::atomic<int> pHeapState;

		void mAllocateFallback(size_t inCapacity);
		void mReleaseFallback(void) noexcept;
		static bool mIsPowerOfTwo(size_t inValue) noexcept;
};

} // namespace ARB

#endif // APRIVATEBUFFERSTORAGE_H
