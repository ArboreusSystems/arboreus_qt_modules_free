// ----------------------------------------------------------
/*!
	\class ASettingsService
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 03/04/2026 at 23:49:31
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "asettingsservice.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

ASettingsService::ASettingsService(QObject* parent) : AThreadServiceTemplate(parent) {

	_A_DEBUG << "ASettingsService created";
}


// -----------
/*!
	\fn

	Doc.
*/

ASettingsService::~ASettingsService(void) {

	_A_DEBUG << "ASettingsService deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

QVariant ASettingsService::mGetValue(QString inKey) {

	return pDriver->mGetValue(inKey);
}


// -----------
/*!
	\fn

	Doc.
*/

void ASettingsService::mSetValue(QString inKey, QVariant inValue) {

	return pDriver->mSetValue(inKey,inValue);
}


// -----------
/*!
	\fn

	Doc.
*/

void ASettingsService::slInit(QObject* inDriver) {

	pDriver = qobject_cast<ASettingsDriver*>(inDriver);

	_A_DEBUG << "ASettingsService initiated";

	emit sgInitiated();
}

