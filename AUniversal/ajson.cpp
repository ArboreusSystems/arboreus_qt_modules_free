// ----------------------------------------------------------
/*!
	\class AJson
	\title
	\brief Template file classes/cpp/file.cpp

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 23/07/2021 at 19:31:23
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "ajson.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

AJson::AJson(QObject* parent) : QObject(parent) {}


// -----------
/*!
	\fn

	Doc.
*/

AJson::~AJson(void) {}


// -----------
/*!
	\fn

	Doc.
*/

bool AJson::mToBase64FileFromObject(QString inPath, QJsonObject inObject) {

	return mToBase64FileFromDocument(
		inPath,QJsonDocument(inObject)
	);
}


// -----------
/*!
	\fn

	Doc.
*/

bool AJson::mToBase64FileFromMap(QString inPath, QVariantMap inMap) {

	return mToBase64FileFromDocument(
		inPath,QJsonDocument(QJsonObject::fromVariantMap(inMap))
	);
}


// -----------
/*!
	\fn

	Doc.
*/

bool AJson::mToBase64FileFromHash(QString inPath, QVariantHash inHash) {

	return mToBase64FileFromDocument(
		inPath,QJsonDocument(QJsonObject::fromVariantHash(inHash))
	);
}


// -----------
/*!
	\fn

	Doc.
*/

bool AJson::mToBase64FileFromDocument(QString inPath, QJsonDocument inDocument) {

	QFile oFile(inPath);
	if (!oFile.open(QFile::WriteOnly)) {
		return false;
	}
	if (oFile.write(inDocument.toJson().toBase64()) >= 0) {
		oFile.close();
		return true;
	}
	return false;
}


// -----------
/*!
	\fn

	Doc.
*/

AJsonFileReply AJson::mFromBase64File(QString inPath) {

	AJsonFileReply oReply = {};

	QFile oJSONFile(inPath);
	if (!oJSONFile.exists()) {
		return oReply;
	}
	if (!oJSONFile.open(QIODevice::ReadOnly|QIODevice::Text)) {
		return oReply;
	}

	QJsonParseError oJSONParseError;
	QJsonDocument oJSONDocument = QJsonDocument::fromJson(
		QByteArray::fromBase64(oJSONFile.readAll()),&oJSONParseError
	);
	if (oJSONDocument.isNull()) {
		return oReply;
	}
	oJSONFile.close();

	oReply.Status = _A_ENUM_STATUS::Ok;
	oReply.Json = oJSONDocument.object();
	return oReply;
}


// -----------
/*!
	\fn bool AJson::mTofileFromObject(QString inPath, QJsonObject inObject)

	Write JSON to file from QJsonObject object.
*/

bool AJson::mToFileFromObject(QString inPath, QJsonObject inObject) {

	return mToFileFromDocument(
		inPath,QJsonDocument(inObject)
	);
}


// -----------
/*!
	\fn bool AJson::mToFileFromMap(QString inPath, QVariantMap inMap)

	Write JSON to file from QVariantMap object.
*/

bool AJson::mToFileFromMap(QString inPath, QVariantMap inMap) {

	return mToFileFromDocument(
		inPath,QJsonDocument(QJsonObject::fromVariantMap(inMap))
	);
}


// -----------
/*!
	\fn bool AJson::mToFileFromHash(QString inPath, QVariantHash inHash)

	Write JSON to file from QVariantHash object.
*/

bool AJson::mToFileFromHash(QString inPath, QVariantHash inHash) {

	return mToFileFromDocument(
		inPath,QJsonDocument(QJsonObject::fromVariantHash(inHash))
	);
}


// -----------
/*!
	\fn bool AJson::mToFileFromDocument(QString inPath, QJsonDocument inDocument)

	Write JSON to file from QJsonDocument object.
*/

bool AJson::mToFileFromDocument(QString inPath, QJsonDocument inDocument) {

	QFile oFile(inPath);
	if (!oFile.open(QFile::WriteOnly)) {
		return false;
	}
	if (oFile.write(inDocument.toJson()) >= 0) {
		oFile.close();
		return true;
	}
	return false;
}


// -----------
/*!
	\fn AJsonFileReply AJson::mFromFile(QString inPath)

	Read JSON from file.
*/

AJsonFileReply AJson::mFromFile(QString inPath) {

	AJsonFileReply oReply = {};

	QFile oJSONFile(inPath);
	if (!oJSONFile.exists()) {
		return oReply;
	}
	if (!oJSONFile.open(QIODevice::ReadOnly|QIODevice::Text)) {
		return oReply;
	}

	QJsonParseError oJSONParseError;
	QJsonDocument oJSONDocument = QJsonDocument::fromJson(
		oJSONFile.readAll(),&oJSONParseError
	);
	if (oJSONDocument.isNull()) {
		return oReply;
	}
	oJSONFile.close();

	oReply.Status = _A_ENUM_STATUS::Ok;
	oReply.Json = oJSONDocument.object();
	return oReply;
}
