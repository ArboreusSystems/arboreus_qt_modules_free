// ----------------------------------------------------------
/*!
	\headerfile ADeviceNativeAndroid
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 23/06/2026 at 13:48:06
	\endlist
*/
// ----------------------------------------------------------
#ifndef ADEVICENATIVEANDROID_H
#define ADEVICENATIVEANDROID_H

// System includes
#include <adevice_pch.h>

// Application includes
#include <adevicenative.h>
#include <alogger.h>

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class ADeviceNativeAndroid : public ADeviceNative {

	Q_OBJECT

	public:

		explicit ADeviceNativeAndroid(QObject *parent = nullptr);
		virtual ~ADeviceNativeAndroid(void);

		void mInit(void) override;
		void mStatusBarStyle(_A_ENUM_DEVICE_STATUS_BAR_STYLE inStyle) override;
};

} // namespace ARB

#endif // ADEVICENATIVEANDROID_H
