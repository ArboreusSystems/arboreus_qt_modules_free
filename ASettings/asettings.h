// ----------------------------------------------------------
/*!
	\headerfile ASettings
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 03/04/2026 at 23:39:38
	\endlist
*/
// ----------------------------------------------------------

#ifndef ASETTINGS_H
#define ASETTINGS_H

// Precompiled includes
#include <asettings_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <asettingsservice.h>
#include <asettingsagentgetvalue.h>
#include <asettingsagentsetvalue.h>
#include <asettingsagentdeletebykey.h>
#include <athreadobjectcontrollertemplate.h>
#include <asettingsdriver.h>

// Constants and definitions

// Namesapces
namespace ARB {

// Class definitions
class ASettings : public AThreadTemplate<ASettingsService> {

	Q_OBJECT

	public:

		explicit ASettings(QObject* parent = nullptr);
		virtual ~ASettings(void);

		void mInit(QObject* inDriver);

	public slots:

		void slInitiated(void);

		QVariant mGetValue(QString inKey);
		void mSetValue(QString inKey,QVariant inValue);
		void mDeleteByKey(QString inKey);

	signals:

		void sgInit(QObject* inDriver);
		void sgInitiated(void);
		void sgSetValue(QString inKey,QVariant inValue);
		void sgDeletedByKey(QString inKey);

};

} // namespace ARB

#endif // ASETTINGS_H
