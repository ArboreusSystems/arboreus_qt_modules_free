// ----------------------------------------------------------
/*!
	\headerfile APrivateBufferStorage
	\title
	\brief Template file wizard/classes/cpp/file.h

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

// Global functions
size_t fPrivateBufferStorage_PageSize(void) noexcept;

// Class definitions
class APrivateBufferStorage {

	public:

		explicit APrivateBufferStorage(qsizetype inCapacity);
		~APrivateBufferStorage(void);

		Q_DISABLE_COPY_MOVE(APrivateBufferStorage)

		char* mData(void) noexcept;
		const char* mConstData(void) const noexcept;
		qsizetype mSize(void) const noexcept;
		void mSizeSet(qsizetype size) noexcept;
		size_t mCapacity(void) const noexcept;
		bool mIsLocked(void) const noexcept;
		void mWipe(void) noexcept;

		static void mZeroing(void* inPointer,size_t inSize) noexcept;

	private:

		char* pPointer = nullptr;
		size_t pAllocated = 0;
		qsizetype pSize = 0;
		bool pMemoryLocked = false;
};

} // namespace ARB

#endif // APRIVATEBUFFERSTORAGE_H
