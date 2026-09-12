// ----------------------------------------------------------
/*!
	\headerfile ADeviceAndroid
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 07/05/2021 at 18:59:45
	\endlist
*/
// ----------------------------------------------------------

#ifndef ADEVICEANDROID_H
#define ADEVICEANDROID_H

// System includes

// Precompiled includes
#include <adevice_pch.h>

// Application includes
#include <adevicedatamodels.h>
#include <adevicemetatypes.h>

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class ADeviceAndroid : public QObject {

	Q_OBJECT

	public:

		explicit ADeviceAndroid(QObject* parent = nullptr);
		virtual ~ADeviceAndroid(void);

		static ADeviceSafeAreaInsets mGetSafeAreaInsets(void);
		static _A_ENUM_DEVICE_TYPE mType(void);
};

} // namespace ARB

#endif // ADEVICEANDROID_H
