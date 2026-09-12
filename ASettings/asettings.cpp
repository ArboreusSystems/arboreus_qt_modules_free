/* -------------------------------------------------------------------
 *  @doc
 *  @notice Template file tablemodel.h
 *
 *  @copyright Arboreus (http://arboreus.systems)
 *  @author Alexandr Kirilov (http://alexandr.kirilov.me)
 *  @created 03/04/2026 at 23:39:38
 * */// --------------------------------------------------------------

// Class header
#include "asettings.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

ASettings::ASettings(QObject* parent) : AThreadTemplate<ASettingsService>(new ASettingsService, parent) {

	this->setPriority(QThread::Priority::LowPriority);

	QObject::connect(
		this,&ASettings::sgInit,
		this->mService(),&ASettingsService::slInit
	);
	QObject::connect(
		this->mService(),&ASettingsService::sgInitiated,
		this,&ASettings::slInitiated
	);

	_A_DEBUG << "ASettings created";
}

// -----------
/*!
	\fn

	Doc.
*/

ASettings::~ASettings(void) {

	_A_DEBUG << "ASettings deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

void ASettings::mInit(QObject* inDriver) {

	emit sgInit(inDriver);
}


// -----------
/*!
	\fn

	Doc.
*/

void ASettings::slInitiated(void) {

	_A_DEBUG << "ASettings initiated";

	emit sgInitiated();
}



// -----------
/*!
	\fn

	Doc.
*/

QVariant ASettings::mGetValue(QString inKey) {

	AThreadObjectControllerTemplate oController;
	QEventLoop oEventLoop;

	ASettingsAgentGetValue oAgent;
	oAgent.pService = this->mService(),
	oAgent.pKey = inKey;
	QObject::connect(
		&oAgent,&ASettingsAgentGetValue::sgFinished,
		&oEventLoop,&QEventLoop::quit
	);
	QObject::connect(
		&oController,&AThreadObjectControllerTemplate::sgRun,
		&oAgent,&ASettingsAgentGetValue::slRun
	);
	oAgent.moveToThread(this);

	emit oController.sgRun();
	oEventLoop.exec();

	if (oAgent.pOutput.pStatus == _A_ENUM_STATUS::Ok) {
		return oAgent.pOutput.pValue;
	} else {
		_A_CRITICAL << "Can't get value from settings for key:" << inKey;
		return QVariant::fromValue(0);
	}
}


// -----------
/*!
	\fn

	Doc.
*/

void ASettings::mSetValue(QString inKey, QVariant inValue) {

	AThreadObjectControllerTemplate oController;
	QEventLoop oEventLoop;

	ASettingsAgentSetValue oAgent;
	oAgent.pService = this->mService(),
	oAgent.pKey = inKey;
	oAgent.pValue = inValue;
	QObject::connect(
		&oAgent,&ASettingsAgentSetValue::sgFinished,
		&oEventLoop,&QEventLoop::quit
	);
	QObject::connect(
		&oController,&AThreadObjectControllerTemplate::sgRun,
		&oAgent,&ASettingsAgentSetValue::slRun
	);
	oAgent.moveToThread(this);

	emit oController.sgRun();
	oEventLoop.exec();

	if (oAgent.pOutput.pStatus == _A_ENUM_STATUS::Ok) {
		_A_DEBUG << "Set key " << inKey << "with value" << inValue;
		emit sgSetValue(inKey,inValue);
	} else {
		_A_CRITICAL << "Can't set value " << inValue << "for key:" << inKey;
	}
}