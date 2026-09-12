// ----------------------------------------------------------
/*!
	\class AApplicationHeartBeat
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/10/2025 at 18:12:48
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "aapplicationheartbeat.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

AApplicationHeartBeat::AApplicationHeartBeat(QObject* parent) : QObject{parent} {

	_A_DEBUG << "AApplicationHeartBeat created";
}


// -----------
/*!
	\fn

	Doc.
*/

AApplicationHeartBeat::~AApplicationHeartBeat(void) {

	_A_DEBUG << "AApplicationHeartBeat deleted";
}
