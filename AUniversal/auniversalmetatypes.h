// ----------------------------------------------------------
/*!
	\headerfile AUniversalMetatypes
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 16/10/2025 at 12:38:05
	\endlist
*/
// ----------------------------------------------------------
#ifndef AUNIVERSALMETATYPES_H
#define AUNIVERSALMETATYPES_H

// Precompiled includes
#include <auniversal_pch.h>

// System includes

// Application includes
#include <auniversaldatamodels.h>
#include <auniversaldefinitions.h>
#include <aenumstatus.h>

// Namesapces

// Constants and definitions
#define _A_META_UNIVERSAL_ENUM_STATUS \
	AEnumStatus::staticMetaObject,"AEnums",1,0,"AEnumStatus",\
	"Can't create AEnumStatus"

// Namespace
namespace ARB {

// Class definitions
class AUniversalMetatypes : public QObject {

	Q_OBJECT

	public:

		explicit AUniversalMetatypes(QObject* parent = nullptr);
		virtual ~AUniversalMetatypes(void);
};

} // namespace ARB

#endif // AUNIVERSALMETATYPES_H
