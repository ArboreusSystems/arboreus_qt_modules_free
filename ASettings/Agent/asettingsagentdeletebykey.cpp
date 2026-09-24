// ----------------------------------------------------------
/*!
	\class ASettingsAgentDeleteByKey
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 24/09/2026 at 17:44:23
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "asettingsagentdeletebykey.h"

// Namesapce
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

ASettingsAgentDeleteByKey::ASettingsAgentDeleteByKey(QObject* parent) : AThreadAgentTemplate(parent) {

	_A_DEBUG << "ASettingsAgentDeleteByKey created";
}


// -----------
/*!
	\fn

	Doc.
*/

ASettingsAgentDeleteByKey::~ASettingsAgentDeleteByKey(void) {

	_A_DEBUG << "ASettingsAgentDeleteByKey deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void ASettingsAgentDeleteByKey::slRun(void) {

	pService->mDeleteByKey(pKey);
	pOutput.pStatus = _A_ENUM_STATUS::Ok;

	emit sgFinished();
}