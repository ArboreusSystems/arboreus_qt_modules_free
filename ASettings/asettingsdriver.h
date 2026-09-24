// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 05/04/2026 at 15:35:22
	\endlist
*/
// ----------------------------------------------------------

#ifndef ASETTINGSDRIVER_H
#define ASETTINGSDRIVER_H

// Precompiled includes
#include <asettings_pch.h>

// System includes

// Application includes
#include <auniversaldefinitions.h>

// Constants and defintions

// Namespace
namespace ARB {

// Class definition
class ASettingsDriver {

	public:

		virtual QVariant mGetValue(QString inKey) = 0;
		virtual void mSetValue(QString inKey,QVariant inValue) = 0;
		virtual void mDeleteByKey(QString inKey) = 0;
};

} // namespace ARB

Q_DECLARE_INTERFACE(ARB::ASettingsDriver,"ARB::ASettingsDriver/1.0")

#endif // ASETTINGSDRIVER_H
