// ----------------------------------------------------------
/*!
	\headerfile AApplication
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 22/09/2025 at 15:00:17
	\endlist
*/
// ----------------------------------------------------------

#ifndef AAPPLICATION_H
#define AAPPLICATION_H

// Precompiled includes
#include <aapplication_pch.h>

// System includes

// Application includes
#include <athreadtemplate.h>
#include <avariables.h>
#include <aapplicationconfig.h>
#include <aloggerdefinitions.h>
#include <aapplicationconfig.h>
#include <aapplicationservice.h>
#include <aapplicationheartbeat.h>
#include <atranslator.h>
#include <apath.h>

// Constants and definitions

// Namesapces
namespace ARB {

// Class definitions
class AApplication : public AThreadTemplate<AApplicationService> {

	Q_OBJECT

	public:

		AApplicationConfig* pConfig = nullptr;
		AVariables* pVariables = nullptr;
		AApplicationHeartBeat* pHeartBeat = nullptr;
		ATranslator* pTranslator = nullptr;
		APath* pPath = nullptr;

		explicit AApplication(QObject* parent = nullptr);
		virtual ~AApplication(void);
		Q_DISABLE_COPY(AApplication)

		void mInit(QObject* inConfig);

	public slots:

		void slInitiated(void);

		void mDeclareAction(QVariantList inAction);
		QString mVersionFull(void);
		QString mVersionShort(void);
		QString mVersionCode(void);
		void mQuit(void);

	signals:

		void sgInit(void);
		void sgInitiated(void);
		void sgDidEnterForeground(void);
		void sgDidEnterBackground(void);
		void sgDeclareAction(QVariantList inAction);

	private:

		ABackend* pBackend = nullptr;
};

} // namespace ARB

#endif // AAPPLICATION_H
