// ----------------------------------------------------------
/*!
	\headerfile AClipboardDriverAndroid
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 13/09/2026 at 08:11:34
	\endlist
*/
// ----------------------------------------------------------
#ifndef ACLIPBOARDDRIVERANDROID_H
#define ACLIPBOARDDRIVERANDROID_H

// Precompiled includes
#include <aclipboard_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <aclipboarddriver.h>

// Constants and definitions

// Global functions
void fAClipboardDriverAndroid_TextCopyPrivate(QString& inText);
void fAClipboardDriverAndroid_TextCopyPrivateAndClear(QString& inText,int inTimeSeconds);
void fAClipboardDriverAndroid_Clear(void);
void fAClipboardDriverAndroid_ClearAfter(int inTimeSeconds);


// Namesapces
namespace ARB {

// Class definitions
class AClipboardDriverAndroid : public AClipboardDriver {

	Q_OBJECT

	public:

		explicit AClipboardDriverAndroid(QObject* parent = nullptr);
		explicit AClipboardDriverAndroid(QClipboard* inClipboard,QObject* parent = nullptr);
		virtual ~AClipboardDriverAndroid(void);

		void mTextCopyPrivate(QString& inText) override;
		void mTextCopyPrivateAndClear(QString& inText,int inTimeoutSeconds) override;

		void mClear(void) override;
		void mClearAfter(int inTimeSeconds) override;

		QString mTextPaste(void) override;
};

} // namespace ARB

#endif // ACLIPBOARDDRIVERANDROID_H
