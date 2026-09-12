// ----------------------------------------------------------
/*!
	\headerfile APath
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 03/04/2026 at 21:23:52
	\endlist
*/
// ----------------------------------------------------------
#ifndef APATH_H
#define APATH_H

// Precompiled includes
#include <aapplication_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <adir.h>
#include <aapplicationconfig.h>

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class APath : public QObject {

	Q_OBJECT

	public:

		explicit APath(QObject* parent = nullptr);
		virtual ~APath(void);

		void mInit(AApplicationConfig* inConfig);

		QString mPathDataApplication(void);
		QString mPathDataConfig(void);
		QString mPathDataCache(void);
		QString mPathDataDocuments(void);

	private:

		AApplicationConfig* pConfig = nullptr;

		QString pPathDataApplication = "NoPathDataApplication";
		QString pPathDataConfig = "NoPathDataConfig";
		QString pPathDataCache = "NoPathDataCache";
		QString pPathDataDocuments = "NoPathDataDocuments";
};

} // namespace ARB

#endif // APATH_H
