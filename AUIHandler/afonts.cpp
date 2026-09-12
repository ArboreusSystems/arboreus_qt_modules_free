// ----------------------------------------------------------
/*!
	\class AFonts
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 08/01/2026 at 22:42:03
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "afonts.h"


// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

AFonts::AFonts(QObject* parent) : QObject(parent) {

	_A_DEBUG << "AFonts created";
}


// -----------
/*!
	\fn

	Doc.
*/

AFonts::~AFonts(void) {

	_A_DEBUG << "AFonts deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void AFonts::mInit(QList<QString> inFontList) {

	this->mSetFontList(inFontList);

	_A_DEBUG << "AFonts initiated";
}


// -----------
/*!
	\fn

	Doc.
*/

QString AFonts::mFontFamily(void) {

	return pFontFamily;
}


// -----------
/*!
	\fn

	Doc.
*/

void AFonts::mSetFont(QString inFontFamily) {

	Q_UNUSED(inFontFamily);

	emit sgFontChanged();
}


// -----------
/*!
	\fn

	Doc.
*/

void AFonts::mSetFontList(QList<QString> inFontList) {

	if (!inFontList.isEmpty()) {

		QFontDatabase::removeAllApplicationFonts();
		for (int i = 0; i < inFontList.size(); ++i) {
			if (QFontDatabase::addApplicationFont(inFontList[i]) < 0) {
				_A_DEBUG << "Can't load font:" << inFontList[i];
			} else {
				_A_DEBUG << "Loaded font:" << inFontList[i];
			}
		}

		QStringList oFontFamilies = QFontDatabase::applicationFontFamilies(0);
		if (!oFontFamilies.isEmpty()) {
			pFontFamily = oFontFamilies.first();
			_A_DEBUG << "Font family:" << pFontFamily;
		} else {
			_A_DEBUG << "No font families";
		}

	} else {
		_A_DEBUG << "Can't load empty list of fonts";
	}
}



