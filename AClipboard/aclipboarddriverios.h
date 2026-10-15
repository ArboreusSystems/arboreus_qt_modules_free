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

// Global functions
void fAClipboardDriverIOS_TextCopyPrivate(QString& inText);
void fAClipboardDriverIOS_TextCopyPrivateAndClear(QString& inText,int inTimeSeconds);
void fAClipboardDriverIOS_Clear(void);
void fAClipboardDriverIOS_ClearAfter(int inTimeSeconds);

// Namesapces
namespace ARB {

// Class definitions
class AClipboardDriverIOS : public AClipboardDriver {

	Q_OBJECT

	public:

		explicit AClipboardDriverIOS(QObject *parent = nullptr);
		explicit AClipboardDriverIOS(QClipboard* inClipboard,QObject* parent = nullptr);
		virtual ~AClipboardDriverIOS(void);

		void mTextCopyPrivate(QString& inText) override;
		void mTextCopyPrivateAndClear(QString& inText,int inTimeSeconds) override;

		void mClear(void) override;
		void mClearAfter(int inTimeSeconds) override;

		void mFlood(void) override;
		void mFloodAfter(int inTimeSeconds) override;

		QString mTextPaste(void) override;
};

} // namespace ARB

#endif // ACLIPBOARDDRIVERIOS_H
