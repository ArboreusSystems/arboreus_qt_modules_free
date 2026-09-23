// ----------------------------------------------------------
/*!
	\class ASecurityNative
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
#include "aprivacynative.h"

// Namesapce
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

APrivacyNative::APrivacyNative(QObject* parent) : QObject(parent) {

	_A_DEBUG << "ASecurityNative created";
}


// -----------
/*!
	\fn

	Doc.
*/

APrivacyNative::~APrivacyNative(void) {

	_A_DEBUG << "APrivacyNative deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivacyNative::mScreen(bool inMode) {

	Q_UNUSED(inMode);

	_A_DEBUG << "There are no screen security for unspecified platform";
}
