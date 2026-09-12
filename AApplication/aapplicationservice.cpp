// ----------------------------------------------------------
/*!
	\class AApplicationService
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/10/2025 at 18:05:20
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "aapplicationservice.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

AApplicationService::AApplicationService(QObject* parent) : AThreadServiceTemplate(parent) {

	_A_DEBUG << "AApplicationService created";
}


// -----------
/*!
	\fn

	Doc.
*/

AApplicationService::~AApplicationService(void) {

	_A_DEBUG << "AApplicationService deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void AApplicationService::slInit(void) {

	_A_DEBUG << "AApplicationService initiated";

	emit this->sgInitiated();
}


