// ----------------------------------------------------------
/*!
	\headerfile ASecurityNativeIOS
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/09/2026 at 21:49:03
	\endlist
*/
// ----------------------------------------------------------
#ifndef APRIVACYNATIVEIOS_H
#define APRIVACYNATIVEIOS_H

// Precompiled includes
#include <aprivacy_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <aprivacynative.h>

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class APrivacyNativeIOS : public APrivacyNative {

	Q_OBJECT

	public:

		explicit APrivacyNativeIOS(QObject* parent = nullptr);
		virtual ~APrivacyNativeIOS(void);

		virtual void mScreen(bool inMode) override;

		void mScreenshotTakenHandler(void);
		void mScreenRecordingHandler(bool isCaptured);
};

} // namespace ARB

#endif // APRIVACYNATIVEIOS_H
