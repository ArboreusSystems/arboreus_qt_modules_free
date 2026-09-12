// ----------------------------------------------------------
/*!
	\headerfile ADeviceNativeIOS
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 22/06/2026 at 13:54:10
	\endlist
*/
// ----------------------------------------------------------
#ifndef ADEVICENATIVEIOS_H
#define ADEVICENATIVEIOS_H

// System includes
#include <adevice_pch.h>

// Application includes
#include <adevicenative.h>
#include <alogger.h>

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class ADeviceNativeIOS : public ADeviceNative {

	Q_OBJECT

	public:

		explicit ADeviceNativeIOS(QObject *parent = nullptr);
		virtual ~ADeviceNativeIOS(void);

		void mInit(void) override;
};

} // namespace ARB

#endif // ADEVICENATIVEIOS_H
