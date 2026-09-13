// ----------------------------------------------------------
/*!
	\headerfile AClipboardDriver
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 13/09/2026 at 08:10:29
	\endlist
*/
// ----------------------------------------------------------
#ifndef ACLIPBOARDDRIVER_H
#define ACLIPBOARDDRIVER_H

// Precompiled includes
#include <aclipboard_pch.h>

// System includes

// Application includes
#include <alogger.h>

// Constants and definitions


// Namesapces
namespace ARB {

// Class definitions
class AClipboardDriver : public QObject {

	Q_OBJECT

	public:

		explicit AClipboardDriver(QObject* parent = nullptr);
		explicit AClipboardDriver(QClipboard* inClipboard,QObject* parent = nullptr);
		virtual ~AClipboardDriver(void);

		virtual void mTextCopySensitiveTo(QString inText);
		virtual void mClear(void);

	protected:

		QClipboard* pClipboard = nullptr;
};

} // namespace ARB

#endif // ACLIPBOARDDRIVER_H
