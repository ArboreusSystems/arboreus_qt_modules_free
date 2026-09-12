// ----------------------------------------------------------
/*!
	\headerfile ASettingsAgentSetValue
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 05/04/2026 at 12:52:34
	\endlist
*/
// ----------------------------------------------------------
#ifndef ASETTINGSAGENTSETVALUE_H
#define ASETTINGSAGENTSETVALUE_H

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
class ASettingsAgentSetValue : public AThreadAgentTemplate {

	Q_OBJECT

	public:

		ASettingsService* pService = nullptr;
		AOutputQVariant pOutput;
		QString pKey = "NoDefinedKey";
		QVariant pValue = QVariant::fromValue(0);

		explicit ASettingsAgentSetValue(QObject* parent = nullptr);
		virtual ~ASettingsAgentSetValue(void);

		void slRun(void);
};

} // namespace ARB

#endif // ASETTINGSAGENTSETVALUE_H
