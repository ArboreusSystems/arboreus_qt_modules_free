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


// Namesapces
namespace ARB {

// Class definitions
class AClipboardDriverMacOS : public AClipboardDriver {

	Q_OBJECT

	public:

		explicit AClipboardDriverMacOS(QObject* parent = nullptr);
		explicit AClipboardDriverMacOS(QClipboard* inClipboard,QObject* parent = nullptr);
		virtual ~AClipboardDriverMacOS(void);

		void mTextCopySensitiveTo(QString inText) override;
		void mClear(void) override;
};

} // namespace ARB

#endif // ACLIPBOARDDRIVERMACOS_H
