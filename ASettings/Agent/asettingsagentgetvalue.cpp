// ----------------------------------------------------------
/*!
	\class ASettingsAgentGetValue
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 05/04/2026 at 12:50:45
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "asettingsagentgetvalue.h"

// Namesapce
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

ASettingsAgentGetValue::ASettingsAgentGetValue(QObject* parent) : AThreadAgentTemplate(parent) {

	_A_DEBUG << "ASettingsAgentGetValue created";
}


// -----------
/*!
	\fn

	Doc.
*/

ASettingsAgentGetValue::~ASettingsAgentGetValue(void) {

	_A_DEBUG << "ASettingsAgentGetValue deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void ASettingsAgentGetValue::slRun(void) {

	pOutput.pValue = pService->mGetValue(pKey);
	pOutput.pStatus = _A_ENUM_STATUS::Ok;

	emit sgFinished();
}

