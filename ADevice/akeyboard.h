// ----------------------------------------------------------
/*!
	\headerfile AKeyboard
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 09/07/2026 at 20:41:40
	\endlist
*/
// ----------------------------------------------------------
#ifndef AKEYBOARD_H
#define AKEYBOARD_H

// Precompiled includes
#include <adevice_pch.h>

// System includes

// Application includes
#include <alogger.h>

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class AKeyboard : public QObject {

	Q_OBJECT

	public:

		explicit AKeyboard(QObject* parent = nullptr);
		virtual ~AKeyboard(void);

	public slots:

		double mHeight(void);
};

} // namespace ARB

#endif // AKEYBOARD_H
