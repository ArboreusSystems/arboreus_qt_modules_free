// ----------------------------------------------------------
/*!
	\class ASettingsAgentSetValue
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 05/04/2026 at 12:52:34
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "asettingsagentsetvalue.h"

// Namesapce
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

ASettingsAgentSetValue::ASettingsAgentSetValue(QObject* parent) : AThreadAgentTemplate(parent) {

	_A_DEBUG << "ASettingsAgentSetValue created";
}


// -----------
/*!
	\fn

	Doc.
*/

ASettingsAgentSetValue::~ASettingsAgentSetValue(void) {

	_A_DEBUG << "ASettingsAgentSetValue deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void ASettingsAgentSetValue::slRun(void) {

	pService->mSetValue(pKey,pValue);
	pOutput.pStatus = _A_ENUM_STATUS::Ok;

	emit sgFinished();
}

