// ----------------------------------------------------------
/*!
	\headerfile ATextEditMobile
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 03/07/2026 at 07:57:21
	\endlist
*/
// ----------------------------------------------------------
#ifndef ATEXTEDITMOBILE_H
#define ATEXTEDITMOBILE_H

// Precompiled includes
#include <aqml_pch.h>

// System includes
#include <QtQuick/private/qquicktextedit_p.h>

// Application includes

// Namespace
namespace ARB {

// Class definitions
class ATextEditMobile : public QQuickTextEdit {

	Q_OBJECT
	QML_ELEMENT

	public:

		explicit ATextEditMobile(QQuickItem* parent = nullptr);
		virtual ~ATextEditMobile(void);

	protected:

		bool eventFilter(QObject* inWatched, QEvent* inEvent);
};

} // namespace ARB

#endif // ATEXTEDITMOBILE_H
