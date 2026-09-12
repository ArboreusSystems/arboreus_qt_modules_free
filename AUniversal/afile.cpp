// ----------------------------------------------------------
/*!
	\class AFile
	\title
	\brief Template file classes/cpp/file.cpp

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 04/03/2022 at 16:36:45
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "afile.h"

// Namespace definition
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

AFile::AFile(QObject* parent) : QObject(parent) {}


// -----------
/*!
	\fn

	Doc.
*/

AFile::~AFile(void) {}


// -----------
/*!
	\fn bool aFile::mRemove(QString inPath)

	Remove file if existed.
*/

bool AFile::mRemove(QString inPath) {

	if (mExist(inPath)) {
		QFile(inPath).remove();
		if (!mExist(inPath)) {
			return true;
		}
		return false;
	}
	return false;
}


// -----------
/*!
	\fn bool aFile::mExist(QString inPath)

	Checking file existance.
*/

bool AFile::mExist(QString inPath) {

	if (QFileInfo::exists(inPath) && !QDir(inPath).exists()) {
		return true;
	}
	return false;
}


// -----------
/*!
	\fn

	Doc.
*/

bool AFile::mEncodeBase64(QString inPath, QByteArray inDatumn) {

	QFile oFile(inPath);
	if (!oFile.open(QFile::WriteOnly)) {
		return false;
	}

	if (oFile.write(inDatumn.toBase64()) >= 0) {
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

AFileReply AFile::mDecodeBase64(QString inPath) {

	AFileReply oReply = {};

	QFile oFile(inPath);
	if (!oFile.exists()) {
		oReply.Status = _A_ENUM_STATUS::NotExisted;
		return oReply;
	}

	if (!oFile.open(QFile::ReadOnly)) {
		return oReply;
	}

	oReply.Status = _A_ENUM_STATUS::Ok;
	oReply.Datumn = QByteArray::fromBase64(oFile.readAll());
	return oReply;
}
