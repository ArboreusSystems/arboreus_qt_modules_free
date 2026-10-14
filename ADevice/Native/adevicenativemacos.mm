// ----------------------------------------------------------
/*!
	\class ADeviceNativeMacOS
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 14/10/2026 at 18:11:48
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "adevicenativemacos.h"

// Private headers
#include "adevicenativemacosprivate.h"


// -----------
// MacOS part
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

ADeviceNativeMacOS::ADeviceNativeMacOS(QObject* parent) : ADeviceNative{parent} {

	_A_DEBUG << "ADeviceNativeMacOS created";
}


// -----------
/*!
	\fn

	Doc.
*/

ADeviceNativeMacOS::~ADeviceNativeMacOS(void) {

	_A_DEBUG << "ADeviceNativeMacOS deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void ADeviceNativeMacOS::mInit(void) {

	_A_DEBUG << "ADeviceNativeMacOS initiated";
}


// -----------
/*!
	\fn

	Doc.
*/

QString ADeviceNativeMacOS::mVendor(void) {

	QString oOutput = "Apple";
	return oOutput;
}


// -----------
/*!
	\fn

	Doc.
*/

QString ADeviceNativeMacOS::mBrand(void) {

	QString oOutput = "Undefined";

	size_t oLength = 0;
	if (sysctlbyname("hw.model",nullptr,&oLength,nullptr,0) == 0 && oLength > 0) {

		QByteArray oBuffer(oLength, 0);
		if (sysctlbyname("hw.model",oBuffer.data(),&oLength,nullptr,0) == 0) {

			QString oModelId = QString::fromUtf8(oBuffer.constData()).trimmed();
			if (oModelId.startsWith("MacBook")) {
				oOutput = "MacBook";
			} else if (oModelId.startsWith("iMac")) {
				oOutput = "iMac";
			} else if (oModelId.startsWith("MacMini") || oModelId.startsWith("Macmini")) {
				oOutput = "MacMini";
			} else if (oModelId.startsWith("MacPro")) {
				oOutput = "MacPro";
			} else if (oModelId.startsWith("Mac")) {

				bool oIsBattery = false;
				CFTypeRef oPowerInfo = IOPSCopyPowerSourcesInfo();
				if (oPowerInfo) {
					CFArrayRef oPowerSources = IOPSCopyPowerSourcesList(oPowerInfo);
					if (oPowerSources) {
						if (CFArrayGetCount(oPowerSources) > 0) oIsBattery = true;
						CFRelease(oPowerSources);
					}
					CFRelease(oPowerInfo);
				}

				if (oIsBattery) {
					oOutput = "MacBook"; // Современный MacBook на Apple Silicon
				} else {
					if (
						oModelId.startsWith("Mac13,1") || oModelId.startsWith("Mac13,2") ||
						oModelId.startsWith("Mac14,13") || oModelId.startsWith("Mac14,14")
						) {
						oOutput = "MacStudio";
					} else {
						oOutput = "MacAppleSilicon";
					}
				}
			}
		}
	}

	return oOutput;
}

QT_END_NAMESPACE