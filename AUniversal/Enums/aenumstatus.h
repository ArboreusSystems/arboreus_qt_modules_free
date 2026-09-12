// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 03/01/2026 at 09:31:38
	\endlist
*/
// ----------------------------------------------------------

#ifndef AENUMSTATUS_H
#define AENUMSTATUS_H

// Precompiled includes
#include <auniversal_pch.h>

// System includes

// Application includes

// Constants and defintions

// Enums definitions
#define _A_ENUM_STATUS ARB::AEnumStatus::AStatus

// Namespace
namespace ARB {

class AEnumStatus: public QObject {

	Q_OBJECT

	public:

		enum class AStatus: int {

			Error = -1,
			Undefined = 0,
			Ok = 1,
			Existed = 2,
			NotExisted = 3,
			WrongProperties = 4,
			WrongValue = 5,
			NoField = 6
		};
		Q_ENUM(AStatus)
};

} // namespace ARB

#endif // AENUMSTATUS_H
