// ----------------------------------------------------------
/*!
	\class APrivateNative
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/09/2026 at 20:40:04
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "aprivatenative.h"

// Namesapce
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

APrivateNative::APrivateNative(QObject* parent) : QObject(parent) {

	_A_DEBUG << "APrivateNative created";
}


// -----------
/*!
	\fn

	Doc.
*/

APrivateNative::~APrivateNative(void) {

	_A_DEBUG << "APrivateNative deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivateNative::mScreen(bool inMode) {

	Q_UNUSED(inMode);

	_A_DEBUG << "There are no screen security for unspecified platform";
}
