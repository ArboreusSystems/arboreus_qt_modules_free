// ----------------------------------------------------------
/*!
	\class ATemplatesMetatypes
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 01/01/2026 at 17:01:06
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "atemplatesmetatypes.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

ATemplatesMetatypes::ATemplatesMetatypes(QObject* parent) : QObject{parent} {}


// -----------
/*!
	\fn

	Doc.
*/

ATemplatesMetatypes::~ATemplatesMetatypes(void) {}


// -----------
/*!
	\fn

	Doc.
*/

void ATemplatesMetatypes::mInit(void) {

	qRegisterMetaType<ARB::AOutputQVariant>("ARB::AOutputQVariant");
	qRegisterMetaType<ARB::AOutputQByteArray>("ARB::AOutputQByteArray");
}

