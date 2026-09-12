// ----------------------------------------------------------
/*!
	\class ALoggerService
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 15/10/2025 at 23:16:22
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "aloggerservice.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

ALoggerService::ALoggerService(QObject* parent) : AThreadServiceTemplate(parent) {

	_A_DEBUG << "ALoggerService created";
}


// -----------
/*!
	\fn

	Doc.
*/

ALoggerService::~ALoggerService(void) {

	_A_DEBUG << "ALoggerService deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void ALoggerService::slInit(ALoggerProperties* inProperties) {

	if (inProperties->Agent) {
		pAgent = qobject_cast<ALoggerAgent*>(inProperties->Agent);
		pAgent->setParent(this);
	} else {
		pAgent = new ALoggerAgent(this);
	}

	QObject::connect(
		this,&ALoggerService::sgInit,
		pAgent,&ALoggerAgent::slInit
	);
	QObject::connect(
		pAgent,&ALoggerAgent::sgInitiated,
		this,&ALoggerService::slInitiated
	);

	emit sgInit(inProperties);
}


// -----------
/*!
	\fn

	Doc.
*/

void ALoggerService::slInitiated(void) {

	_A_DEBUG << "ALoggerService initiated";

	emit sgInitiated();
}


// -----------
/*!
	\fn

	Doc.
*/

void ALoggerService::slWriteToLog(ALoggerMessageModel inModel) {

	pAgent->mWriteToLog(inModel);
}
