// ----------------------------------------------------------
/*!
	\class ATextInputMobile
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 03/07/2026 at 07:52:57
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "atextinputmobile.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

ATextInputMobile::ATextInputMobile(QQuickItem* parent) {

	this->installEventFilter(this);
}


// -----------
/*!
	\fn

	Doc.
*/

ATextInputMobile::~ATextInputMobile(void) {}


// -----------
/*!
	\fn

	Doc.
*/

bool ATextInputMobile::eventFilter(QObject* inWatched, QEvent* inEvent) {

#ifdef Q_OS_IOS

	if (inWatched == this && inEvent->type() == QEvent::InputMethodQuery) {

		auto* oInputMethodQueryEvent = static_cast<QInputMethodQueryEvent*>(inEvent);
		if (oInputMethodQueryEvent->queries() & Qt::ImCursorRectangle) {

			QVariant oValueRectangle = oInputMethodQueryEvent->value(Qt::ImCursorRectangle);
			if (oValueRectangle.isValid()) QRectF oRect = oValueRectangle.toRectF();

			oInputMethodQueryEvent->setValue(Qt::ImCursorRectangle,QRectF());

			unsigned long oRemainingQueries = oInputMethodQueryEvent->queries() & ~Qt::ImCursorRectangle;
			if (oRemainingQueries == 0) return true;
		}
	}

#endif

	return QQuickItem::eventFilter(inWatched,inEvent);
}
