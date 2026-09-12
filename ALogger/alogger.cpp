/* -------------------------------------------------------------------
 *  @doc
 *  @notice Template file tablemodel.h
 *
 *  @copyright Arboreus (http://arboreus.systems)
 *  @author Alexandr Kirilov (http://alexandr.kirilov.me)
 *  @created 23/09/2025 at 08:13:13
 * */// --------------------------------------------------------------

// Class header
#include <alogger.h>

// Namespace
using namespace ARB;

// Global variables
ALogger* gLogger = nullptr;
bool gLoggerInitiated = false;
bool gLoggerStopping = false;
QList<ARB::ALoggerMessageModel> gLoggerMessageCache = {};


// -----------
/*!
	\fn

	Doc.
*/


ALogger::ALogger(QObject* parent) : AThreadTemplate<ALoggerService>(new ALoggerService,parent) {

	QObject::connect(
		this,&ALogger::sgInit,
		this->mService(),&ALoggerService::slInit,
		Qt::QueuedConnection
	);
	QObject::connect(
		this->mService(),&ALoggerService::sgInitiated,
		this,&ALogger::slInitiated,
		Qt::QueuedConnection
	);
	QObject::connect(
		this,&ALogger::sgWriteToLog,
		this->mService(),&ALoggerService::slWriteToLog
	);

	_A_DEBUG << "ALogger created";
}


// -----------
/*!
	\fn

	Doc.
*/

ALogger::~ALogger(void) {

	_A_DEBUG << "ALogger deleted";
}


// -----------
/*!
	\fn

	Doc.
*/

ALogger& ALogger::mInstance(void) {

	static ALogger oInstance;
	gLogger = &oInstance;
	return oInstance;
}


// -----------
/*!
	\fn

	Doc.
*/

void ALogger::mInit(ALoggerProperties* inProperties) {

	if (inProperties->Agent) {
		inProperties->Agent->moveToThread(this);
	}

	emit sgInit(inProperties);
}


// -----------
/*!
	\fn

	Doc.
*/

void ALogger::mMessageHandler(QtMsgType inType, const QMessageLogContext& inContext, const QString& inMessage) {

	ALoggerMessageModel oMessageModel = ALogger::mCreateModel(inType,inContext,inMessage);

	if (gLoggerInitiated) {
		gLogger->mWriteToLog(oMessageModel);
	} else {
		gLoggerMessageCache.append(oMessageModel);
	}
}


// -----------
/*!
	\fn

	Doc.
*/

ALoggerMessageModel ALogger::mCreateModel(QtMsgType inType, const QMessageLogContext& inContext, const QString& inMessage) {

	QString oThreadIDString = QString("0x%1");
	QString oThreadIDValue = oThreadIDString.arg((long)QThread::currentThread(),0,16);

	ALoggerMessageModel oMessageModel;
	oMessageModel.Type = inType;
	oMessageModel.Time = QDateTime::currentMSecsSinceEpoch();
	oMessageModel.ThreadID = oThreadIDValue.toUtf8();
	oMessageModel.Message = inMessage.toUtf8();

	QString oAuthorString = inMessage.left(3);
	std::string oAuthor = oAuthorString.toStdString();
	if (
		oAuthor == _A_LOGGER_DEFAULT_STRING_USER ||
		oAuthor == _A_LOGGER_DEFAULT_STRING_SYSTEM ||
		oAuthor == _A_LOGGER_DEFAULT_STRING_NETWORK
	) {
		oMessageModel.Author = oAuthor.c_str();
	} else {
		oMessageModel.Author = _A_LOGGER_DEFAULT_STRING_SYSTEM;
	}

#ifdef QT_DEBUG

	oMessageModel.File = inContext.file ? inContext.file : "no file";
	oMessageModel.Function = inContext.function ? inContext.function : "no function";
	oMessageModel.Line = inContext.line;

#endif

	return oMessageModel;
}


// -----------
/*!
	\fn

	Doc.
*/

void ALogger::mWriteToLog(ALoggerMessageModel inMessage) {

	emit sgWriteToLog(inMessage);
}


// -----------
/*!
	\fn

	Doc.
*/

void ALogger::slInitiated(void) {

	for (int i = 0; i < gLoggerMessageCache.length(); i++) {
		this->mWriteToLog(gLoggerMessageCache.at(i));
	}
	gLoggerMessageCache.clear();
	gLoggerInitiated = true;

	_A_DEBUG << "ALogger initiated";

	emit sgInitiated();
}

