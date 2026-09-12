// ----------------------------------------------------------
/*!
	\headerfile ATranslator
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 01/04/2026 at 14:03:50
	\endlist
*/
// ----------------------------------------------------------
#ifndef ATRANSLATOR_H
#define ATRANSLATOR_H

// Precompiled includes
#include <aapplication_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <aapplicationconfig.h>

// Constants and definitions

// Namesapces
namespace ARB {

// Class definitions
class ATranslator : public QObject {

	Q_OBJECT

	public:

		explicit ATranslator(QObject* parent = nullptr);
		virtual ~ATranslator(void);

		void mInit(AApplicationConfig* inConfig);

	public slots:

		QString mLocaleGet(void);
		void mLocaleSet(QString inLocale);
		QVariantList mLocaleList(void);

	signals:

		void sgLocaleChanged(QString inLocale);

	private:

		AApplicationConfig* pConfig = nullptr;
		QTranslator* pTranslator = nullptr;
		QString pLocale = "en";

		QString mLocaleDefault(void);
		QString mlocaleResourceName(void);
		bool mLocaleCheck(QString inLocale);
};

} // namespace ARB

#endif // ATRANSLATOR_H
