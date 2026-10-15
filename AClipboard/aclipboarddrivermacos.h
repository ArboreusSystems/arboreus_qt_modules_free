// ----------------------------------------------------------
/*!
	\headerfile AClipboardDriverMacOS
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 13/09/2026 at 09:16:31
	\endlist
*/
// ----------------------------------------------------------
#ifndef ACLIPBOARDDRIVERMACOS_H
#define ACLIPBOARDDRIVERMACOS_H

// Precompiled includes
#include <aclipboard_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <aclipboarddriver.h>

// Constants and definitions

// Global functions
void fAClipboardDriverMacOS_TextCopyPrivate(QString& inText);
void fAClipboardDriverMacOS_TextCopyPrivateAndClear(QString& inText,int inTimeSeconds);
void fAClipboardDriverMacOS_Clear(void);
void fAClipboardDriverMacOS_ClearAfter(int inTimeSeconds);

// Namesapces
namespace ARB {

// Class definitions
class AClipboardDriverMacOS : public AClipboardDriver {

	Q_OBJECT

	public:

		explicit AClipboardDriverMacOS(QObject* parent = nullptr);
		explicit AClipboardDriverMacOS(QClipboard* inClipboard,QObject* parent = nullptr);
		virtual ~AClipboardDriverMacOS(void);

		void mTextCopyPrivate(QString& inText) override;
		void mTextCopyPrivateAndClear(QString& inText,int inTimeoutSeconds) override;

		void mClear(void) override;
		void mClearAfter(int inTimeoutSeconds) override;

		QString mTextPaste(void) override;
};

} // namespace ARB

#endif // ACLIPBOARDDRIVERMACOS_H
