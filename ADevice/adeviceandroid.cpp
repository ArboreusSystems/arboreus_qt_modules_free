// ----------------------------------------------------------
/*!
	\class ADeviceAndroid
	\title
	\brief Template file classes/cpp/file.cpp

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 07/05/2021 at 18:59:45
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "adeviceandroid.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

ADeviceAndroid::ADeviceAndroid(QObject* parent) : QObject(parent) {}


// -----------
/*!
	\fn

	Doc.
*/

ADeviceAndroid::~ADeviceAndroid(void) {}


// -----------
/*!
	\fn

	Doc.
*/

ADeviceSafeAreaInsets ADeviceAndroid::mGetSafeAreaInsets(void) {

	ADeviceSafeAreaInsets oOutput;

	// TODO: ARBDM-73 Add SafeArea insets to Android version

	return oOutput;
}


// -----------
/*!
	\fn

	Doc.
*/

_A_ENUM_DEVICE_TYPE ADeviceAndroid::mType(void) {

	_A_ENUM_DEVICE_TYPE oOutput = _A_ENUM_DEVICE_TYPE::Undefined;

	// TODO: ARBDM-74 Add device type detection to Android version

	return oOutput;
}
