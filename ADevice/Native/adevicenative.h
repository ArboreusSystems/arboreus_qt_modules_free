// ----------------------------------------------------------
/*!
	\headerfile ADeviceNative
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 22/06/2026 at 13:53:42
	\endlist
*/
// ----------------------------------------------------------
#ifndef ADEVICENATIVE_H
#define ADEVICENATIVE_H

// Precompiled includes
#include <adevice_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <aenumdevicetype.h>
#include <adevicemetatypes.h>

// Constants and definitions


// Namespace
namespace ARB {

// Class definitions
class ADeviceNative : public QObject {

	Q_OBJECT

	public:

		explicit ADeviceNative(QObject *parent = nullptr);
		virtual ~ADeviceNative(void);

		virtual void mInit(void);
		virtual _A_ENUM_DEVICE_TYPE mType(void);
		virtual void mStatusBarStyle(_A_ENUM_DEVICE_STATUS_BAR_STYLE inStyle);
};

} // namespace ARB

#endif // ADEVICENATIVE_H
