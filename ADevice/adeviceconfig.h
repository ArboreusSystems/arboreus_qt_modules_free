// ----------------------------------------------------------
/*!
    \headerfile %{CN}
    \title
    \brief Template file files/cppheader/file.h

    \list
    \li @notice Template file classes/file.h
    \li @copyright Arboreus (http://arboreus.systems)
    \li @author Alexandr Kirilov (http://alexandr.kirilov.me)
    \li @created 11/02/2026 at 12:43:27
    \endlist
*/
// ----------------------------------------------------------

#ifndef ADEVICECONFIG_H
#define ADEVICECONFIG_H

// Precompiled includes

// System includes

// Application includes
#include <adevicemetatypes.h>

// Constants and defintions

// Namespace
namespace ARB {

// Class definition
class ADeviceConfig {

	public:

		virtual QString ADeviceConfig_NameApplicationComponent(void) = 0;
        virtual _A_ENUM_DEVICE_STATUS_BAR_STYLE ADeviceConfig_StatusBarStyle(void) = 0;
};

} // namespace ARB

Q_DECLARE_INTERFACE(ARB::ADeviceConfig,"ARB::ADeviceConfig/1.0")

#endif // ADEVICECONFIG_H
