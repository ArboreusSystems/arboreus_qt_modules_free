// ----------------------------------------------------------
/*!
	\headerfile ATextInputMobile
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 03/07/2026 at 07:52:57
	\endlist
*/
// ----------------------------------------------------------
#ifndef ATEXTINPUTMOBILE_H
#define ATEXTINPUTMOBILE_H

// Precompiled includes
#include <aqml_pch.h>

// System includes
#include <QtQuick/private/qquicktextinput_p.h>

// Application includes

// Namespace
namespace ARB {

// Class definitions
class ATextInputMobile : public QQuickTextInput {

	Q_OBJECT
	QML_ELEMENT

	public:

		explicit ATextInputMobile(QQuickItem* parent = nullptr);
		virtual ~ATextInputMobile(void);

	protected:

		bool eventFilter(QObject* inWatched, QEvent* inEvent);
};

} // namespace ARB

#endif // ATEXTINPUTMOBILE_H
