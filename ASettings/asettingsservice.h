// ----------------------------------------------------------
/*!
	\headerfile ASettingsService
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 03/04/2026 at 23:49:31
	\endlist
*/
// ----------------------------------------------------------
#ifndef ASETTINGSSERVICE_H
#define ASETTINGSSERVICE_H

// Precompiled includes
#include <asettings_pch.h>

// System includes

// Application includes
#include <athreadservicetemplate.h>
#include <alogger.h>
#include <adir.h>
#include <auniversaldefinitions.h>
#include <asettingsdriver.h>

// Namesapces

// Constants and definitions

// Namesapces
namespace ARB {

// Class definitions
class ASettingsService : public AThreadServiceTemplate {

	Q_OBJECT

	public:

		explicit ASettingsService(QObject* parent = nullptr);
		virtual ~ASettingsService(void);

		QVariant mGetValue(QString inKey);
		void mSetValue(QString inKey,QVariant inValue);

	public slots:

		void slInit(QObject* inDriver);

	signals:

		void sgInit(void);
		void sgInitiated(void);

	private:

		ASettingsDriver* pDriver = nullptr;
};

} // namespace ARB

#endif // ASETTINGSSERVICE_H
