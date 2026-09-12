// ----------------------------------------------------------
/*!
	\class ATranslator
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 01/04/2026 at 14:03:50
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "atranslator.h"

// Namespace
using namespace ARB;

// Global variables
extern QGuiApplication* gGuiApplication;
extern QQmlApplicationEngine* gApplicationEngine;


// -----------
/*!
	\fn

	Doc.
*/

ATranslator::ATranslator(QObject* parent) : QObject{parent} {

	pTranslator = new QTranslator(this);

	_A_DEBUG << "ATranslator created";
}


// -----------
/*!
	\fn

	Doc.
*/

ATranslator::~ATranslator(void) {

	_A_DEBUG << "ATranslator deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void ATranslator::mInit(AApplicationConfig* inConfig) {

	pConfig = inConfig;

	_A_DEBUG << "ATranslator initiated";
}


// -----------
/*!
	\fn

	Doc.
*/

QString ATranslator::mLocaleGet(void) {

	return pLocale;
}


// -----------
/*!
	\fn

	Doc.
*/

void ATranslator::mLocaleSet(QString inLocale) {

	pLocale = mLocaleDefault();
	if (mLocaleCheck(inLocale)) {
		pLocale = inLocale;
	} else {
		_A_CRITICAL << "Wrong locale prefix";
	}

	if (pTranslator->load(mlocaleResourceName().arg(pLocale))) {
		gGuiApplication->installTranslator(pTranslator);
		gApplicationEngine->retranslate();
		_A_DEBUG << "Translation for" << pLocale << "loaded";
		emit sgLocaleChanged(inLocale);
	} else {
		_A_CRITICAL << "Translation for" << pLocale << "not loaded";
	}
}


// -----------
/*!
	\fn

	Doc.
*/

QVariantList ATranslator::mLocaleList(void) {

	return pConfig->AApplicationConfig_Translator_LocaleList();
}


// -----------
/*!
	\fn

	Doc.
*/

QString ATranslator::mLocaleDefault(void) {

	return pConfig->AApplicationConfig_Translator_LocaleDefault();
}


// -----------
/*!
	\fn

	Doc.
*/

QString ATranslator::mlocaleResourceName(void) {

	return pConfig->AApplicationConfig_Translator_ResourceName();
}


// -----------
/*!
	\fn

	Doc.
*/

bool ATranslator::mLocaleCheck(QString inLocale) {

	QVariantList oLocaleList = mLocaleList();
	if (oLocaleList.contains(inLocale)) {
		return true;
	} else {
		_A_CRITICAL << "Wrong locale:" << inLocale;
		return false;
	}
}
