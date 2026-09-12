// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 23/06/2026 at 14:49:06
	\endlist
*/
// ----------------------------------------------------------

#ifndef AENUMSTATUSBARSTYLE_H
#define AENUMSTATUSBARSTYLE_H

// Precompiled includes
#include <adevice_pch.h>

// System includes

// Application includes

// Constants and defintions

// Enums definitions
#define _A_ENUM_DEVICE_STATUS_BAR_STYLE ARB::AEnumStatusBarStyle::AStatusBarStyle

// Namespace
namespace ARB {

class AEnumStatusBarStyle: public QObject {

	Q_OBJECT

	public:

		enum class AStatusBarStyle: int {

			Undefined = 0,
			Light = 1,
			Dark = 2,
			Default = 3
		};
		Q_ENUM(AStatusBarStyle)
};

} // namespace ARB

#endif // AENUMSTATUSBARSTYLE_H
