// ----------------------------------------------------------
/*!
	\class ADeviceNative
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 22/06/2026 at 13:53:42
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "adevicenative.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

ADeviceNative::ADeviceNative(QObject* parent) : QObject{parent} {}


// -----------
/*!
	\fn

	Doc.
*/

ADeviceNative::~ADeviceNative(void) {}


// -----------
/*!
	\fn

	Doc.
*/

void ADeviceNative::mInit(void) {}


// -----------
/*!
	\fn

	Doc.
*/

_A_ENUM_DEVICE_TYPE ADeviceNative::mType(void) {

	_A_ENUM_DEVICE_TYPE oOutput = _A_ENUM_DEVICE_TYPE::Undefined;

#ifdef Q_OS_MACOS
	oOutput = _A_ENUM_DEVICE_TYPE::Desktop;
#else
	QScreen* oScreen = QGuiApplication::primaryScreen();
	qreal oPhysicalWidthInch = oScreen->physicalSize().width() / 25.4;
	qreal oPhysicalHeightInch = oScreen->physicalSize().height() / 25.4;
	qreal oDiagonal = qSqrt((oPhysicalWidthInch * oPhysicalWidthInch) + (oPhysicalHeightInch * oPhysicalHeightInch));
	if(oDiagonal < 7.0) {
		oOutput = _A_ENUM_DEVICE_TYPE::Phone;
	} else {
		oOutput = _A_ENUM_DEVICE_TYPE::Tablet;
	}
#endif

	return oOutput;
}


// -----------
/*!
	\fn

	Doc.
*/

void ADeviceNative::mStatusBarStyle(AEnumStatusBarStyle::AStatusBarStyle inStyle) {}

