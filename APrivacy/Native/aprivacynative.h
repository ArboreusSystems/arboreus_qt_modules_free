// ----------------------------------------------------------
/*!
	\headerfile ASecurityNative
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/09/2026 at 20:40:04
	\endlist
*/
// ----------------------------------------------------------
#ifndef APRIVACYNATIVE_H
#define APRIVACYNATIVE_H

// Precompiled includes
#include <aprivacy_pch.h>

// System includes

// Application includes
#include <alogger.h>

// Namespace
namespace ARB {

// Class definitions
class APrivacyNative : public QObject {

	Q_OBJECT

	public:

		explicit APrivacyNative(QObject* parent = nullptr);
		virtual ~APrivacyNative(void);

		virtual void mScreen(bool inMode);

	signals:

		void sgScreenshotTaken(void);
		void sgScreenRecordingChanged(bool isCaptured);
};

} // namespace ARB

#endif // APRIVACYNATIVE_H
