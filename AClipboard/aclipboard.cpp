/* -------------------------------------------------------------------
 *  @doc
 *  @notice Template file tablemodel.h
 *
 *  @copyright Arboreus (http://arboreus.systems)
 *  @author Alexandr Kirilov (http://alexandr.kirilov.me)
 *  @created 28/06/2026 at 11:19:05
 * */// --------------------------------------------------------------

// Class header
#include "aclipboard.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

AClipboard::AClipboard(QObject* parent) : QObject(parent) {

	_A_DEBUG << "AClipboard created";
}


// -----------
/*!
	\fn

	Doc.
*/

AClipboard::~AClipboard(void) {

	_A_DEBUG << "AClipboard deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboard::mInit(void) {

	pClipboard = QGuiApplication::clipboard();

	_A_DEBUG << "AClipboard initiated";
	emit sgInitiated();
}

// -----------
/*!
	\fn

	Doc.
*/

QStringList AClipboard::mMIMETypes(void) {

	QStringList oOutput;

	const QMimeData* oMimeData = pClipboard->mimeData();
	if (oMimeData) oOutput = oMimeData->formats();

	return oOutput;
}


// -----------
/*!
	\fn

	Doc.
*/

bool AClipboard::mHasImage(void) {

	bool oOutput = false;

	const QMimeData* oMimeData = pClipboard->mimeData();
	if (oMimeData) oOutput = oMimeData->hasImage();

	return oOutput;
}


// -----------
/*!
	\fn

	Doc.
*/

bool AClipboard::mHasText(void) {

	bool oOutput = false;

	const QMimeData* oMimeData = pClipboard->mimeData();
	if (oMimeData) oOutput = oMimeData->hasText();

	return oOutput;
}


// -----------
/*!
	\fn

	Doc.
*/

bool AClipboard::mHasURLs(void) {

	bool oOutput = false;

	const QMimeData* oMimeData = pClipboard->mimeData();
	if (oMimeData) oOutput = oMimeData->hasUrls();

	return oOutput;
}


// -----------
/*!
	\fn

	Doc.
*/

bool AClipboard::mHasColor(void) {

	bool oOutput = false;

	const QMimeData* oMimeData = pClipboard->mimeData();
	if (oMimeData) oOutput = oMimeData->hasColor();

	return oOutput;
}

// -----------
/*!
	\fn

	Doc.
*/

bool AClipboard::mHasHTML(void) {

	bool oOutput = false;

	const QMimeData* oMimeData = pClipboard->mimeData();
	if (oMimeData) oOutput = oMimeData->hasHtml();

	return oOutput;
}


// -----------
/*!
	\fn

	Doc.
*/

QString AClipboard::mTextPasteFrom(void) {

	QString oOutput = "";
	if (mHasText()) oOutput = pClipboard->text();
	return oOutput;
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboard::mTextCopyTo(QString inText) {

	pClipboard->setText(inText,QClipboard::Clipboard);
}
