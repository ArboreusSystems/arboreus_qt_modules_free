// ----------------------------------------------------------
/*!
	\headerfile APrivateBuffer
	\title
	\brief Template file wizard/classes/cpp/file.h

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

		bool mIsNull(void) const noexcept;
		bool mIsEmpty(void) const noexcept;
		qsizetype mSize(void) const noexcept;
		bool mIsLocked(void) const noexcept;
		static bool mDisableCoreDumps(void) noexcept;
		const char* mConstData(void) const noexcept;
		QByteArrayView mView(void) const noexcept;
		QByteArray mToByteArray(void) const;
		QString mToQString(void) const;
		QVariant mToVariant(void) const;
		void mClear(void) noexcept;

		static void mWipe(QByteArray& inBytes);
		static void mWipe(QString& inText);

	private:

		std::shared_ptr<APrivateBufferStorage> pStorageData;

		explicit APrivateBuffer(qsizetype inCapacity);
};

} // namespace ARB

Q_DECLARE_METATYPE(ARB::APrivateBuffer)

#endif // APRIVATEBUFFER_H
