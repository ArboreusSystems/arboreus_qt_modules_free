// ----------------------------------------------------------
/*!
	\headerfile ADeviceMetatypes
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 12/02/2026 at 09:31:08
	\endlist
*/
// ----------------------------------------------------------
#ifndef ADEVICEMETATYPES_H
#define ADEVICEMETATYPES_H

// Precompiled includes
#include <adevice_pch.h>

// System includes

// Application includes
#include <aenumdevicetype.h>
#include <aenumplatform.h>
#include <aenumstatusbarstyle.h>

// Namesapces

// Constants and definitions
#define _A_META_DEVICE_ENUM_DEVICE_TYPE \
	AEnumDeviceType::staticMetaObject,"AEnums",1,0,"AEnumDeviceType",\
	"Can't create AEnumDeviceType"
#define _A_META_DEVICE_ENUM_PLATFORM \
	AEnumPlatform::staticMetaObject,"AEnums",1,0,"AEnumPlatform",\
	"Can't create AEnumPlatform"
#define _A_META_DEVICE_ENUM_STATUS_BAR_STYLE \
	AEnumStatusBarStyle::staticMetaObject,"AEnums",1,0,"AEnumStatusBarStyle",\
	"Can't create AEnumStatusBarStyle"

// Namespace
namespace ARB {

// Class definitions
class ADeviceMetatypes : public QObject {

	Q_OBJECT

	public:

		explicit ADeviceMetatypes(QObject* parent = nullptr);
		virtual ~ADeviceMetatypes(void);
};

} // namespace ARB

#endif // ADEVICEMETATYPES_H
