// ----------------------------------------------------------
/*!
	\class AVariables
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 15/02/2026 at 10:07:39
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "avariables.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

AVariables::AVariables(QObject* parent) : QObject(parent) {}


// -----------
/*!
	\fn

	Doc.
*/

AVariables::~AVariables(void) {}


// -----------
/*!
	\fn

	Doc.
*/

void AVariables::mSetSignal(bool inSignal) {

	pSignal = inSignal;
}


// -----------
/*!
	\fn

	Doc.
*/

QVariantMap AVariables::mGetAll(void) {

	return pStorage;
}


// -----------
/*!
	\fn

	Doc.
*/

QVariant AVariables::mGet(QString inKey) {

	QVariant oOutput = pStorage.value(inKey);
	return oOutput;
}


// -----------
/*!
	\fn

	Doc.
*/

QVariant AVariables::mGetWithDefault(QString inKey, QVariant inDefault) {

	QVariant oOutput = pStorage.value(inKey,inDefault);
	return oOutput;
}


// -----------
/*!
	\fn

	Doc.
*/

void AVariables::mSet(QString inKey, QVariant inVariable) {

	pStorage.insert(inKey,inVariable);
	if (pSignal) {
		emit this->sgUpdated();
	}
}
