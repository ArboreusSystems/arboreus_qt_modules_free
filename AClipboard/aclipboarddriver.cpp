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

void AClipboardDriver::mTextCopySensitiveTo(QString inText) {

	Q_UNUSED(inText);

	_A_INFO << "AClipboardDriver unsupported platform for copying sensitive text";
}


// -----------
/*!
	\fn

	Doc.
*/

void AClipboardDriver::mClear(void) {

	_A_INFO << "AClipboardDriver unsupported platform for clearing";
}
