// ----------------------------------------------------------
/*!
	\headerfile APrivateBuffer
	\title
	\brief Implicitly shared (copy-on-write) UTF-8 buffer for secrets,
	backed by APrivateBufferStorage (OpenSSL secure heap / locked mmap).

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/11/2026 at 19:40:04
	\endlist
*/
// ----------------------------------------------------------

#ifndef APRIVATEBUFFER_H
#define APRIVATEBUFFER_H

// Precompiled includes
#include <aprivate_pch.h>

// System includes

// Application includes
#include <aprivatebufferstorage.h>

// Namesapces

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class APrivateBuffer {

	public:

		APrivateBuffer(void) noexcept = default;
		explicit APrivateBuffer(QByteArray&& inByteArray);
		explicit APrivateBuffer(QString&& inString);
		explicit APrivateBuffer(QVariant&& inVariant);
		~APrivateBuffer(void);

		APrivateBuffer(const APrivateBuffer&) = default;
		APrivateBuffer(APrivateBuffer&& inOther) noexcept;
		APrivateBuffer& operator=(const APrivateBuffer&) = default;
		APrivateBuffer& operator=(APrivateBuffer&& inOther) noexcept;

		bool mIsNull(void) const noexcept;
		bool mIsEmpty(void) const noexcept;
		qsizetype mSize(void) const noexcept;
		qsizetype mSymbolCount(void) const noexcept;
		qsizetype mCodePointCount(void) const noexcept;
		qsizetype mCapacity(void) const noexcept;
		bool mIsLocked(void) const noexcept;
		bool mIsSecureHeap(void) const noexcept;
		static bool mDisableCoreDumps(void) noexcept;
		const char* mConstData(void) const noexcept;
		QByteArrayView mView(void) const noexcept;
		QByteArray mToByteArray(void) const;
		QString mToQString(void) const;
		QVariant mToVariant(void) const;
		bool mIsEqual(const APrivateBuffer& inOther) const noexcept;
		bool mIsEqual(QByteArrayView inBytes) const noexcept;
		void mClear(void) noexcept;

		void mReserve(qsizetype inCapacity);
		void mAppend(QChar inSymbol);
		void mAppend(char32_t inCodePoint);
		void mAppend(QStringView inText);
		void mAppend(QByteArrayView inBytes);
		void mAppend(const APrivateBuffer& inOther);
		qsizetype mPopBack(qsizetype inCount = 1);

		static void mWipe(QByteArray& inBytes);
		static void mWipe(QString& inText);

	private:

		static constexpr qsizetype pMinimumGrowth = 64;
		static constexpr char32_t pReplacementCharacter = 0xFFFD;

		std::shared_ptr<APrivateBufferStorage> pStorageData;
		char16_t pPendingHighSurrogate = 0;

		explicit APrivateBuffer(qsizetype inCapacity);

		char* mPrepareAppend(qsizetype inExtraBytes);
		void mDetach(qsizetype inCapacity,qsizetype inKeepBytes);
		void mAppendRaw(const char* inBytes,qsizetype inSize);
		void mFlushPendingSurrogate(void);

		static qsizetype mEncodeUtf8(char32_t inCodePoint,char* outBytes) noexcept;
		static bool mOverlaps(const char* inPointer,const char* inBegin,qsizetype inSize) noexcept;
};

} // namespace ARB

Q_DECLARE_METATYPE(ARB::APrivateBuffer)

#endif // APRIVATEBUFFER_H
