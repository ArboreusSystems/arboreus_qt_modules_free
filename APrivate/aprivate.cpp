/* -------------------------------------------------------------------
 *  @doc
 *  @notice Template file tablemodel.h
 *
 *  @copyright Arboreus (http://arboreus.systems)
 *  @author Alexandr Kirilov (http://alexandr.kirilov.me)
 *  @created 21/09/2026 at 20:33:09
 * */// --------------------------------------------------------------

// Class header
#include "aprivate.h"

// Namesapce
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

APrivate::APrivate(QObject* parent) : QObject(parent) {

#ifdef Q_OS_IOS
	pNative = qobject_cast<APrivateNative*>(new APrivateNativeIOS(this));
#elif defined(Q_OS_ANDROID)
	pNative = qobject_cast<APrivateNative*>(new APrivateNativeAndroid(this));
#elif defined(Q_OS_MACOS)
	pNative = new APrivateNative(this);
#endif

	QObject::connect(
		pNative,&APrivateNative::sgScreenshotTaken,
		this,&APrivate::slScreenshotTaken
	);
	QObject::connect(
		pNative,&APrivateNative::sgScreenRecordingChanged,
		this,&APrivate::slScreenRecordingChanged
	);

	_A_DEBUG << "APrivate created";
}


// -----------
/*!
	\fn

	Doc.
*/

APrivate::~APrivate(void) {

	_A_DEBUG << "APrivate deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivate::mInit(void) {

	_A_DEBUG << "APrivate initiated";

	emit sgInitiated();
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivate::mScreen(bool inMode) {

	pNative->mScreen(inMode);
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivate::slScreenshotTaken(void) {

	_A_DEBUG << "Screenshot taken";

	emit this->sgScreenshotTaken();
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivate::slScreenRecordingChanged(bool inCaptured) {

	_A_DEBUG << "Screens recording status changed" << inCaptured;

	emit this->sgScreenRecordingChanged(inCaptured);
}
