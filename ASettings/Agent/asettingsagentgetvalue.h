// ----------------------------------------------------------
/*!
	\headerfile ASettingsAgentGetValue
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 05/04/2026 at 12:50:45
	\endlist
*/
// ----------------------------------------------------------
#ifndef ASETTINGSAGENTGETVALUE_H
#define ASETTINGSAGENTGETVALUE_H

// Precompiled includes
#include <asettings_pch.h>

// System includes

// Application includes
#include <athreadagenttemplate.h>
#include <alogger.h>
#include <aoutputqvariant.h>
#include <asettingsservice.h>

// Constants and definitions

// Namesapces
namespace ARB {

// Class definitionss
class ASettingsAgentGetValue : public AThreadAgentTemplate {

	Q_OBJECT

	public:

		ASettingsService* pService = nullptr;
		AOutputQVariant pOutput;
		QString pKey = "NoDefinedKey";

		explicit ASettingsAgentGetValue(QObject* parent = nullptr);
		virtual ~ASettingsAgentGetValue(void);

		void slRun(void);
};

} // namespace ARB

#endif // ASETTINGSAGENTGETVALUE_H
