// ----------------------------------------------------------
/*!
    \headerfile %{CN}
    \title
    \brief Template file files/cppheader/file.h

    \list
    \li @notice Template file classes/file.h
    \li @copyright Arboreus (http://arboreus.systems)
    \li @author Alexandr Kirilov (http://alexandr.kirilov.me)
    \li @created 12/02/2026 at 09:40:45
    \endlist
*/
// ----------------------------------------------------------

#ifndef AENUMDEVICETYPE_H
#define AENUMDEVICETYPE_H

// Precompiled includes
#include <adevice_pch.h>

// System includes

// Application includes

// Constants and defintions

// Enums definitions
#define _A_ENUM_DEVICE_TYPE ARB::AEnumDeviceType::ADeviceType

// Namespace
namespace ARB {

class AEnumDeviceType: public QObject {

	Q_OBJECT

	public:

		enum class ADeviceType: int {

			Undefined = 0,
			Phone = 1,
			Tablet = 2,
			Desktop = 3
		};
		Q_ENUM(ADeviceType)
};

} // namespace ARB

#endif // AENUMDEVICETYPE_H
