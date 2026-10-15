// ----------------------------------------------------------
/*!
	\class AClipboardDriver
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 13/09/2026 at 08:10:29
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "aclipboarddriver.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

AClipboardDriver::AClipboardDriver(QObject* parent)	: QObject(parent) {

	_A_DEBUG << "AClipboardDriver created";
}

// -----------
/*!
	\fn

	Doc.
*/

AClipboardDriver::AClipboardDriver(QClipboard* inClipboard, QObject* parent) : QObject(parent) {

	pClipboard = inClipboard;

	_A_DEBUG << "AClipboardDriver created with clipboard";
}


// -----------
/*!
	\fn

	Doc.
*/

AClipboardDriver::~AClipboardDriver(void) {

	_A_DEBUG << "AClipboardDriver deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriver::mTextCopyPrivate(QString inText) {

	Q_UNUSED(inText);

    _A_INFO << "AClipboardDriver unsupported platform for copying private text";
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriver::mTextCopyPrivateAndClear(QString inText, int inTimeoutSeconds) {

	Q_UNUSED(inText);
	Q_UNUSED(inTimeoutSeconds);

	_A_INFO << "AClipboardDriver unsupported platform for copying private text and clear";
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriver::mClear(void) {

	_A_INFO << "AClipboardDriver unsupported platform for clearing";
}


// -----------
/*!
    \fn

    Doc.
*/

void AClipboardDriver::mClearAfter(int inTimeSeconds) {

	_A_INFO << "AClipboardDriver unsupported platform for clearing after";
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriver::mFlood(void) {

	_A_INFO << "AClipboardDriver unsupported platform for flooding";
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriver::mFloodAfter(int inTimeSeconds) {

	_A_INFO << "AClipboardDriver unsupported platform for flooding after";
}


// -----------
/*!
	\fn

	Doc.
*/

QString AClipboardDriver::mTextPaste(void) {

	_A_INFO << "AClipboardDriver unsupported platform for text pasting";

	QString oOutput;
	return oOutput;
}
