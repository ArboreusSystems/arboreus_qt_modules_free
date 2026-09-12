// ----------------------------------------------------------
/*!
	\headerfile ATemplatesMetatypes
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 01/01/2026 at 17:01:06
	\endlist
*/
// ----------------------------------------------------------
#ifndef ATEMPLATESMETATYPES_H
#define ATEMPLATESMETATYPES_H

// Precompiled includes
#include <atemplates_pch.h>

// System includes

// Application includes
#include <aoutputqvariant.h>
#include <aoutputqbytearray.h>

// Namesapces

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class ATemplatesMetatypes : public QObject {

	Q_OBJECT

	public:

		explicit ATemplatesMetatypes(QObject* parent = nullptr);
		virtual ~ATemplatesMetatypes(void);

		static void mInit(void);
};

} // namespace ARB

#endif // ATEMPLATESMETATYPES_H
