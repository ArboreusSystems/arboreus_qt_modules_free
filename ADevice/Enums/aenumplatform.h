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

#ifndef AENUMPLATFORM_H
#define AENUMPLATFORM_H

// Precompiled includes
#include <adevice_pch.h>

// System includes

// Application includes

// Constants and defintions

// Enums definitions
#define _A_ENUM_PLATFORM ARB::AEnumPlatform::APlatform

// Namespace
namespace ARB {

class AEnumPlatform: public QObject {

	Q_OBJECT

	public:

		enum class APlatform: int {

			Undefined = 0,
			IOS = 1,
			Android = 2,
			MacOS = 3
		};
		Q_ENUM(APlatform)
};

} // namespace ARB

#endif // AENUMPLATFORM_H
