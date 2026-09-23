/* -------------------------------------------------------------------
 *  @doc
 *  @notice Template file tablemodel.h
 *
 *  @copyright Arboreus (http://arboreus.systems)
 *  @author Alexandr Kirilov (http://alexandr.kirilov.me)
 *  @created 21/09/2026 at 20:33:09
 * */// --------------------------------------------------------------

// Class header
#include "aprivacy.h"

// Namesapce
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

APrivacy::APrivacy(QObject* parent) : QObject(parent) {

#ifdef Q_OS_IOS
	pNative = qobject_cast<APrivacyNative*>(new APrivacyNativeIOS(this));
#elif defined(Q_OS_ANDROID)
	pNative = qobject_cast<APrivacyNative*>(new APrivacyNativeAndroid(this));
#elif defined(Q_OS_MACOS)
	pNative = new APrivacyNative(this);
#endif

	QObject::connect(
		pNative,&APrivacyNative::sgScreenshotTaken,
		this,&APrivacy::slScreenshotTaken
	);
	QObject::connect(
		pNative,&APrivacyNative::sgScreenRecordingChanged,
		this,&APrivacy::slScreenRecordingChanged
	);

	_A_DEBUG << "APrivacy created";
}


// -----------
/*!
	\fn

	Doc.
*/

APrivacy::~APrivacy(void) {

	_A_DEBUG << "APrivacy deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivacy::mInit(void) {

	_A_DEBUG << "APrivacy initiated";

	emit sgInitiated();
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivacy::mScreen(bool inMode) {

	_A_DEBUG << "APrivacy::mScreen";

	pNative->mScreen(inMode);
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivacy::slScreenshotTaken(void) {

	_A_DEBUG << "Screenshot taken";

	emit this->sgScreenshotTaken();
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivacy::slScreenRecordingChanged(bool inCaptured) {

	_A_DEBUG << "Screens recording status changed" << inCaptured;

	emit this->sgScreenRecordingChanged(inCaptured);
}
