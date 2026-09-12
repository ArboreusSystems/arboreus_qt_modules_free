// ----------------------------------------------------------
/*!
	\class APath
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 03/04/2026 at 21:23:52
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "apath.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

APath::APath(QObject* parent) : QObject{parent} {

	_A_DEBUG << "APath created";
}


// -----------
/*!
	\fn

	Doc.
*/

APath::~APath(void) {

	_A_DEBUG << "APath deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void APath::mInit(AApplicationConfig* inConfig) {

	if (inConfig) {

		pConfig = inConfig;

		pPathDataApplication = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) +
			"/" + pConfig->AApplicationConfig_Application_Organisation() +
			"/" + pConfig->AApplicationConfig_Application_Name();
		if (ADir::mEnsure(pPathDataApplication)) {
			_A_DEBUG << "Ensured Application Data path:" << pPathDataApplication;
		} else {
			_A_CRITICAL << "No Application Data path:" << pPathDataApplication;
		}

		pPathDataConfig = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) +
			"/" + pConfig->AApplicationConfig_Application_Organisation() +
			"/" + pConfig->AApplicationConfig_Application_Name();
		if (ADir::mEnsure(pPathDataConfig)) {
			_A_DEBUG << "Ensured Config Data path:" << pPathDataConfig;
		} else {
			_A_CRITICAL << "No Config Data path:" << pPathDataConfig;
		}

		pPathDataCache = QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation) +
			"/" + pConfig->AApplicationConfig_Application_Organisation() +
			"/" + pConfig->AApplicationConfig_Application_Name();
		if (ADir::mEnsure(pPathDataCache)) {
			_A_DEBUG << "Ensured Cache Data path:" << pPathDataCache;
		} else {
			_A_CRITICAL << "No Cache Data path:" << pPathDataCache;
		}

		pPathDataDocuments = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
			"/" + pConfig->AApplicationConfig_Application_Organisation() +
			"/" + pConfig->AApplicationConfig_Application_Name();
		if (ADir::mEnsure(pPathDataDocuments)) {
			_A_DEBUG << "Ensured Documents Data path:" << pPathDataDocuments;
		} else {
			_A_CRITICAL << "No Documents Data path:" << pPathDataDocuments;
		}

	} else {
		_A_CRITICAL << "No required AApplicationConfig";
	}
}


// -----------
/*!
	\fn

	Doc.
*/

QString APath::mPathDataApplication(void) {

	return pPathDataApplication;
}


// -----------
/*!
	\fn

	Doc.
*/

QString APath::mPathDataConfig(void) {

	return pPathDataConfig;
}


// -----------
/*!
	\fn

	Doc.
*/

QString APath::mPathDataCache(void) {

	return pPathDataCache;
}


// -----------
/*!
	\fn

	Doc.
*/

QString APath::mPathDataDocuments(void) {

	return pPathDataDocuments;
}

