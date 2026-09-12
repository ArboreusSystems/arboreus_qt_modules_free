// ----------------------------------------------------------
/*!
	\headerfile AFonts
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 08/01/2026 at 22:42:03
	\endlist
*/
// ----------------------------------------------------------
#ifndef AFONTS_H
#define AFONTS_H

// Precompiled includes
#include <auihandler_pch.h>

// System includes

// Application includes
#include <alogger.h>

// Constants and definitions

// Namesapces
namespace ARB {

// Class definitions
class AFonts : public QObject {

	Q_OBJECT

	public:

		explicit AFonts(QObject* parent = nullptr);
		virtual ~AFonts(void);
		Q_DISABLE_COPY(AFonts)

		void mInit(QList<QString> inFontList);

	public slots:

		QString mFontFamily(void);
		void mSetFont(QString inFontFamily);

	signals:

		void sgFontChanged(void);

	private:

		QString pFontFamily = QString("NoFontFamily");

		void mSetFontList(QList<QString> inFontList);
};

} // namespace ARB

#endif // AFONTS_H
