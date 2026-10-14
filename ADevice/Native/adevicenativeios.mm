// ----------------------------------------------------------
/*!
	\class ADeviceNativeIOS
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 22/06/2026 at 13:54:10
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "adevicenativeios.h"

// Private includes
#include <adevicenativeiosprivate.h>


// -----------
// IOS part
// -----------


// -----------
// Qt part
// -----------

QT_BEGIN_NAMESPACE

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

ADeviceNativeIOS::ADeviceNativeIOS(QObject* parent) : ADeviceNative(parent) {
	
	_A_DEBUG << "ADeviceNativeIOS created";
}


// -----------
/*!
	\fn

	Doc.
*/

ADeviceNativeIOS::~ADeviceNativeIOS(void) {

	_A_DEBUG << "ADeviceNativeIOS deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void ADeviceNativeIOS::mInit(void) {

	_A_DEBUG << "ADeviceNativeIOS initiated";
}


// -----------
/*!
	\fn

	Doc.
*/

QString ADeviceNativeIOS::mVendor(void) {

	QString oOutput = "Apple";
	return oOutput;
}


// -----------
/*!
	\fn

	Doc.
*/

QString ADeviceNativeIOS::mBrand(void) {

	QString oOutput	= "Undefined";

	UIUserInterfaceIdiom oIdiom = [UIDevice currentDevice].userInterfaceIdiom;
	if (oIdiom == UIUserInterfaceIdiomPhone) {
		oOutput = "iPhone";
	} else if (oIdiom == UIUserInterfaceIdiomPad) {
		oOutput = "iPad";
	} else {
		oOutput = "OtheriOS";
	}

	return oOutput;
}

QT_END_NAMESPACE
