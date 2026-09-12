// ----------------------------------------------------------
/*!
	\class ADevice
	\title
	\brief Template file classes/cpp/file.cpp

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 07/05/2021 at 18:44:46
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "adevice.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

ADevice::ADevice(QObject* parent) : QObject(parent) {

	pConfig = qobject_cast<ADeviceConfig*>(gConfig);

	pScreen = QGuiApplication::primaryScreen();
	QObject::connect(
		pScreen,&QScreen::orientationChanged,
		this,&ADevice::slOrientationChanged
	);

#ifdef Q_OS_IOS
	pPlatform = _A_ENUM_PLATFORM::IOS;
	pNative = new ADeviceNativeIOS(this);
#elif defined(Q_OS_ANDROID)
	pPlatform = _A_ENUM_PLATFORM::Android;
	pNative = new ADeviceNativeAndroid(this);
#elif defined(Q_OS_MACOS)
	pPlatform = _A_ENUM_PLATFORM::MacOS;
	pNative = new ADeviceNative(this);
#endif

	pKeyboard = new AKeyboard(this);

	_A_DEBUG << "ADevice created";
}


// -----------
/*!
	\fn

	Doc.
*/

ADevice::~ADevice(void) {

	_A_DEBUG << "ADevice deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void ADevice::mInit(void) {

	pNative->mInit();
	pNative->mStatusBarStyle(pConfig->ADeviceConfig_StatusBarStyle());
	pType = pNative->mType();

	_A_DEBUG << "ADevice initiated";

	emit sgInitiated();
}


// -----------
/*!
	\fn

	Doc.
*/

_A_ENUM_DEVICE_TYPE ADevice::mType(void) {

	return pType;
}


// -----------
/*!
	\fn

	Doc.
*/

_A_ENUM_PLATFORM ADevice::mPlatform(void) {

	return pPlatform;
}


// -----------
/*!
	\fn

	Doc.
*/

bool ADevice::mIsLandscape(void) {

	return pScreen->isLandscape(
		pScreen->orientation()
	);
}


// -----------
/*!
	\fn

	Doc.
*/

void ADevice::mStatusBarStyle(_A_ENUM_DEVICE_STATUS_BAR_STYLE inStyle) {

	pNative->mStatusBarStyle(inStyle);
}


// -----------
/*!
	\fn

	Doc.
*/

void ADevice::slOrientationChanged(Qt::ScreenOrientation inOrientation) {

	switch (inOrientation) {
		case Qt::PortraitOrientation:
			_A_DEBUG << "Changed orientation 'Portrait':" << inOrientation;
			break;
		case Qt::LandscapeOrientation:
			_A_DEBUG << "Changed orientation 'Landscape':" << inOrientation;
			break;
		case Qt::InvertedLandscapeOrientation:
			_A_DEBUG << "Changed orientation 'Inverted Landscape':" << inOrientation;
			break;
		case Qt::InvertedPortraitOrientation:
			_A_DEBUG << "Changed orientation 'Inverted Portrait':" << inOrientation;
			break;
		default:
			_A_DEBUG << "Changed orientation 'Undefined':" << inOrientation;
			break;
	}

	emit sgOrientationChanged(inOrientation);
}



