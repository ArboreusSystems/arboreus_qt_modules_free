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
#ifndef APRIVATENATIVEIOS_H
#define APRIVATENATIVEIOS_H

// Precompiled includes
#include <aprivate_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <aprivatenative.h>

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class APrivateNativeIOS : public APrivateNative {

	Q_OBJECT

	public:

		explicit APrivateNativeIOS(QObject* parent = nullptr);
		virtual ~APrivateNativeIOS(void);

		virtual void mScreen(bool inMode) override;

		void mScreenshotTakenHandler(void);
		void mScreenRecordingHandler(bool isCaptured);
};

} // namespace ARB

#endif // APRIVATENATIVEIOS_H
