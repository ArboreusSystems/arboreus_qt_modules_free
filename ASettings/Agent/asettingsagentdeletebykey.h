// ----------------------------------------------------------
/*!
	\headerfile ASettingsAgentDeleteByKey
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 24/09/2026 at 17:44:23
	\endlist
*/
// ----------------------------------------------------------
#ifndef ASETTINGSAGENTDELETEBYKEY_H
#define ASETTINGSAGENTDELETEBYKEY_H

// Precompiled includes
#include <asettings_pch.h>

// System includes

// Application includes
#include <athreadagenttemplate.h>
#include <aoutputqvariant.h>
#include <alogger.h>
#include <asettingsservice.h>

// Constants and definitions

// Namesapces
namespace ARB {

// Class definitionss
class ASettingsAgentDeleteByKey : public AThreadAgentTemplate {

	Q_OBJECT

	public:

		ASettingsService* pService = nullptr;
		AOutputQVariant pOutput;
		QString pKey = "NoDefinedKey";

		explicit ASettingsAgentDeleteByKey(QObject *parent = nullptr);
		virtual ~ASettingsAgentDeleteByKey(void);

		void slRun(void);
};

} // namespace ARB

#endif // ASETTINGSAGENTDELETEBYKEY_H
