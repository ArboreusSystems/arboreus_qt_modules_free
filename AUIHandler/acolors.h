// ----------------------------------------------------------
/*!
	\headerfile AColors
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 08/01/2026 at 22:51:42
	\endlist
*/
// ----------------------------------------------------------
#ifndef ACOLORS_H
#define ACOLORS_H

// Precompiled includes
#include <auihandler_pch.h>

// System includes

// Application includes
#include <alogger.h>

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class AColors : public QObject {

	Q_OBJECT

	public:

		QColor pTransparent = QColor(Qt::transparent).rgba();

		explicit AColors(QObject* parent = nullptr);
		virtual ~AColors(void);
		Q_DISABLE_COPY(AColors)

		void mInit(QMap<QString,QString> inColorStrings);
		void mInitColors(QMap<QString,QString> inColorStrings);
		QColor mGetColor(QString inKey);

	public slots:

		QString mGetString(QString inKey);
		QVariantList mGetListOfStringColors(void);
		QVariantList mGetListOfStringNames(void);
		QString mTransparent(void);

	signals:

		void sgColorsInitiated(void);

	private:

		QMap<QString,QString> pColorStrings = {};
		QMap<QString,QColor> pColors = {};
		QString pDefaultColor = "magenta";
};

} // namespace ARB

#endif // ACOLORS_H
