// ----------------------------------------------------------
/*!
	\class ADeviceNativeAndroid
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 23/06/2026 at 13:48:06
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "adevicenativeandroid.h"

// Namespace
using namespace ARB;
using namespace QNativeInterface;


// -----------
/*!
	\fn

	Doc.
*/

ADeviceNativeAndroid::ADeviceNativeAndroid(QObject* parent) : ADeviceNative(parent) {

	_A_DEBUG << "ADeviceNativeAndroid created";
}


// -----------
/*!
	\fn

	Doc.
*/

ADeviceNativeAndroid::~ADeviceNativeAndroid(void) {

	_A_DEBUG << "ADeviceNativeAndroid deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void ADeviceNativeAndroid::mInit(void) {

	_A_DEBUG << "ADeviceNativeAndroid initiated";
}


// -----------
/*!
	\fn

	Doc.
*/

void ADeviceNativeAndroid::mStatusBarStyle(_A_ENUM_DEVICE_STATUS_BAR_STYLE inStyle) {

	bool oAppearance = true;
	if (inStyle == _A_ENUM_DEVICE_STATUS_BAR_STYLE::Light) oAppearance = false;

	QAndroidApplication::runOnAndroidMainThread([oAppearance]() {

		QJniObject oActivity = QNativeInterface::QAndroidApplication::context();
		if (!oActivity.isValid()) return;

		QJniObject oWindow = oActivity.callObjectMethod("getWindow","()Landroid/view/Window;");
		QJniObject oDecorView = oWindow.callObjectMethod("getDecorView","()Landroid/view/View;");

		QJniObject oInsetsController = QJniObject::callStaticObjectMethod(
			"androidx/core/view/WindowCompat",
			"getInsetsController",
			"(Landroid/view/Window;Landroid/view/View;)Landroidx/core/view/WindowInsetsControllerCompat;",
			oWindow.object(),
			oDecorView.object()
		);
		oInsetsController.callMethod<void>("setAppearanceLightStatusBars","(Z)V",oAppearance);
	});
}



