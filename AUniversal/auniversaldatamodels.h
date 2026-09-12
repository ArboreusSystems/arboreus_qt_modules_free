// ----------------------------------------------------------
/*!
	\headerfile
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 11/09/2021 at 18:10:21
	\endlist
*/
// ----------------------------------------------------------
#ifndef AUNIVERSALDATAMODELS_H
#define AUNIVERSALDATAMODELS_H

// Precompiled includes
#include <auniversal_pch.h>

// System includes

// Application includes
#include <auniversaldefinitions.h>

// Constants and defintions

// Namespace
namespace ARB {

class AFileReply {

	public:

		_A_ENUM_STATUS Status = _A_ENUM_STATUS::Error;
		QByteArray Datumn = 0;
};

} // namespace ARB

Q_DECLARE_METATYPE(ARB::AFileReply)


// Namespace
namespace ARB {

class AJsonFileReply {

	public:

		_A_ENUM_STATUS Status = _A_ENUM_STATUS::Error;
		QJsonObject Json;
};

} // namespace ARB

Q_DECLARE_METATYPE(ARB::AJsonFileReply)


// Namespace
namespace ARB {

class AJsonFieldReply {

	public:

		_A_ENUM_STATUS Status = _A_ENUM_STATUS::Error;
		QVariant Value;
};

} // namespace ARB

Q_DECLARE_METATYPE(ARB::AJsonFieldReply)

#endif // AUNIVERSALDATAMODELS_H
