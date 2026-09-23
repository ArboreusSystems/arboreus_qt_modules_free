// ----------------------------------------------------------
/*!
	\class ASecurityNativeAndroid
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/09/2026 at 21:48:32
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "aprivacynativeandroid.h"

// Namesapce
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

APrivacyNativeAndroid::APrivacyNativeAndroid(QObject* parent) : APrivacyNative(parent) {

	_A_DEBUG << "ASecurityNativeAndroid created";
}


// -----------
/*!
	\fn

	Doc.
*/

APrivacyNativeAndroid::~APrivacyNativeAndroid(void) {

	_A_DEBUG << "ASecurityNativeAndroid deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivacyNativeAndroid::mScreen(bool inMode) {

	const jint oFlagSecure = 8192;

	QNativeInterface::QAndroidApplication::runOnAndroidMainThread([inMode,oFlagSecure]() {

		QJniObject oActivity = QNativeInterface::QAndroidApplication::context();
		if (!oActivity.isValid()) {
			_A_CRITICAL << "Android activity is inValid";
			return;
		}

		QJniObject oWindow = oActivity.callObjectMethod("getWindow","()Landroid/view/Window;");
		if (!oWindow.isValid()) {
			_A_CRITICAL << "Android windoe is inValid";
			return;
		}

		if (inMode) {
			oWindow.callMethod<void>("addFlags","(I)V",oFlagSecure);
			_A_DEBUG << "Screen security enabled";
		} else {
			oWindow.callMethod<void>("clearFlags","(I)V",oFlagSecure);
			_A_DEBUG << "Screen security disabled";
		}

	}).waitForFinished();
}
