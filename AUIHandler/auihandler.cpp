/* -------------------------------------------------------------------
 *  @doc
 *  @notice Template file tablemodel.h
 *
 *  @copyright Arboreus (http://arboreus.systems)
 *  @author Alexandr Kirilov (http://alexandr.kirilov.me)
 *  @created 08/01/2026 at 19:30:41
 * */// --------------------------------------------------------------

// Class header
#include "auihandler.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

AUIHandler::AUIHandler(QObject* parent) : QObject(parent) {

	pFonts = new AFonts(this);
	pColors = new AColors(this);
	pUIConfig = new AUIConfig(this);

	_A_DEBUG << "AUIHandler created";
}


// -----------
/*!
	\fn

	Doc.
*/

AUIHandler::~AUIHandler(void) {

	_A_DEBUG << "AUIHandler deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void AUIHandler::mInit(QObject* inConfig) {

	pConfig = qobject_cast<AUIHandlerConfig*>(inConfig);

	pFonts->mInit(pConfig->AUIHandlerConfig_Fonts());
	pColors->mInit(pConfig->AUIHandlerConfig_Colors());
	pUIConfig->mInit(pConfig);

	_A_DEBUG << "AUIHandler initiated";

	emit sgInitiated();
}

