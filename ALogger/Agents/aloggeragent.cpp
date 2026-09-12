// ----------------------------------------------------------
/*!
	\class ALoggerAgent
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 19/10/2025 at 15:44:29
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "aloggeragent.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

ALoggerAgent::ALoggerAgent(QObject* parent) : QObject{parent} {

	_A_DEBUG << "ALoggerAgent created";
}


// -----------
/*!
	\fn

	Doc.
*/

ALoggerAgent::~ALoggerAgent(void) {

	_A_DEBUG << "ALoggerAgent deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void ALoggerAgent::mWriteToLog(ALoggerMessageModel inMessage) {

	Q_UNUSED(inMessage);
}


// -----------
/*!
	\fn

	Doc.
*/

void ALoggerAgent::mOnStopping(QtMsgType inType, const QMessageLogContext& inContext, const QString& inMessage) {

	Q_UNUSED(inType);
	Q_UNUSED(inContext);
	Q_UNUSED(inMessage);
}


// -----------
/*!
	\fn

	Doc.
*/

void ALoggerAgent::slInit(ALoggerProperties* inProperties) {

	Q_UNUSED(inProperties);
	_A_DEBUG << "ALoggerAgent initiated";

	emit sgInitiated();
}

