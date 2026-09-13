// ----------------------------------------------------------
/*!
	\headerfile AClipboardDriverIOS
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 13/09/2026 at 08:12:03
	\endlist
*/
// ----------------------------------------------------------
#ifndef ACLIPBOARDDRIVERIOS_H
#define ACLIPBOARDDRIVERIOS_H

// Precompiled includes
#include <aclipboard_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <aclipboarddriver.h>

// Constants and definitions


// Namesapces
namespace ARB {

// Class definitions
class AClipboardDriverIOS : public AClipboardDriver {

	Q_OBJECT

	public:

		explicit AClipboardDriverIOS(QObject *parent = nullptr);
		explicit AClipboardDriverIOS(QClipboard* inClipboard,QObject* parent = nullptr);
		virtual ~AClipboardDriverIOS(void);

		virtual void mTextCopySensitiveTo(QString inText);
		virtual void mClear(void);
};

} // namespace ARB

#endif // ACLIPBOARDDRIVERIOS_H
