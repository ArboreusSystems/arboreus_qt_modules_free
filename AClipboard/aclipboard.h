// ----------------------------------------------------------
/*!
	\headerfile AClipboard
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 28/06/2026 at 11:19:05
	\endlist
*/
// ----------------------------------------------------------

#ifndef ACLIPBOARD_H
#define ACLIPBOARD_H

// Precompiled includes
#include <aclipboard_pch.h>

// System includes

// Application includes
#include <alogger.h>


// Namesapces
namespace ARB {

// Class definitions
class AClipboard : public QObject {

	Q_OBJECT

	public:

		explicit AClipboard(QObject* parent = nullptr);
		virtual ~AClipboard(void);

		void mInit(void);

	public slots:

		QStringList mMIMETypes(void);

		bool mHasImage(void);
		bool mHasText(void);
		bool mHasURLs(void);
		bool mHasColor(void);
		bool mHasHTML(void);

		QString mTextPasteFrom(void);
		void mTextCopyTo(QString inText);

	signals:

		void sgInitiated(void);

	private:

		QClipboard* pClipboard = nullptr;
};

} // namespace ARB

#endif // ACLIPBOARD_H
