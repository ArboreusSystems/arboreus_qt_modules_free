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

// Precompiled includes
#include <adevice_pch.h>

// System includes

// Application includes
#include <adevicenativeioshandler.h>

// Constants and definitions

// Class header
#include "adevicenativeios.h"


// -----------
// IOS part
// -----------

@implementation ADeviceIOSNativehandler

-(instancetype) init {
	
	self = [super init];
	if (self) {
		
	}
	return self;
}

@end


// -----------
// Qt part
// -----------

QT_BEGIN_NAMESPACE

// Namespace
using namespace ARB;

// Global variables
ADeviceIOSNativehandler* gDeviceNativeIOSHandler = nullptr;


// -----------
/*!
	\fn

	Doc.
*/

ADeviceNativeIOS::ADeviceNativeIOS(QObject* parent) : ADeviceNative{parent} {
	
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

	gDeviceNativeIOSHandler = [[ADeviceIOSNativehandler alloc] init];

	_A_DEBUG << "ADeviceNativeIOS initiated";
}

QT_END_NAMESPACE
