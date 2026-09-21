/* -------------------------------------------------------------------
 *  @doc
 *  @notice Template file tablemodel.h
 *
 *  @copyright Arboreus (http://arboreus.systems)
 *  @author Alexandr Kirilov (http://alexandr.kirilov.me)
 *  @created 22/09/2025 at 15:00:17
 * */// --------------------------------------------------------------

// Class header
#include <aapplication.h>

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

AApplication::AApplication(QObject* parent) : AThreadTemplate<AApplicationService>(new AApplicationService, parent) {

	pHeartBeat = new AApplicationHeartBeat(this);
	pVariables = new AVariables(this);
	pTranslator = new ATranslator(this);
	pPath = new APath(this);

	QObject::connect(
		this,&AApplication::sgInit,
		this->mService(),&AApplicationService::slInit
	);
	QObject::connect(
		this->mService(),&AApplicationService::sgInitiated,
		this,&AApplication::slInitiated
	);

	_A_DEBUG << "AApplication created";
}


// -----------
/*!
	\fn

	Doc.
*/

AApplication::~AApplication(void) {

	_A_DEBUG << "AApplication deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void AApplication::mInit(QObject* inConfig) {

	pConfig = qobject_cast<AApplicationConfig*>(inConfig);

	pTranslator->mInit(pConfig);
	pPath->mInit(pConfig);

	emit sgInit();
}


// -----------
/*!
	\fn

	Doc.
*/

void AApplication::slInitiated(void) {

	_A_DEBUG << "AApplication initated";

	emit sgInitiated();
}


// -----------
/*!
	\fn

	Doc.
*/

void AApplication::mDeclareAction(QVariantList inAction) {

	_A_DEBUG << "Action appeared" << qvariant_cast<QString>(inAction[1]) << "by" << qvariant_cast<QString>(inAction[0]);
	emit sgDeclareAction(inAction);
}


// -----------
/*!
	\fn

	Doc.
*/

QString AApplication::mVersionFull(void) {

	return pConfig->AApplicationConfig_Application_VersionFull();
}


// -----------
/*!
	\fn

	Doc.
*/

QString AApplication::mVersionShort(void) {

	return pConfig->AApplicationConfig_Application_VersionShort();
}


// -----------
/*!
	\fn

	Doc.
*/

QString AApplication::mVersionCode(void) {

	return pConfig->AApplicationConfig_Application_VersionCode();
}


// -----------
/*!
	\fn

	Doc.
*/

void AApplication::mQuit(void) {

	qApp->quit();
}