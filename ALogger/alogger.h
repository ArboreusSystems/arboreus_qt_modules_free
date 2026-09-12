// ----------------------------------------------------------
/*!
	\headerfile ALogger
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 23/09/2025 at 08:13:13
	\endlist
*/
// ----------------------------------------------------------

#ifndef ALOGGER_H
#define ALOGGER_H

// Precompiled includes
#include <alogger_pch.h>

// System includes

// Application includes
#include <athreadtemplate.h>
#include <aloggerdefinitions.h>
#include <aloggerdatamodels.h>
#include <aloggerservice.h>

// Constants and definitions

// Namesapces
namespace ARB {

// Class definitions
class ALogger : public AThreadTemplate<ALoggerService> {

	Q_OBJECT

	public:

		static ALogger& mInstance(void);
		void mInit(ALoggerProperties* inProperties);

		static void mMessageHandler(
			QtMsgType inType,
			const QMessageLogContext& inContext,
			const QString& inMessage
		);
		static ALoggerMessageModel mCreateModel(
			QtMsgType inType,
			const QMessageLogContext& inContext,
			const QString& inMessage
		);
		void mWriteToLog(ALoggerMessageModel inMessage);

	public slots:

		void slInitiated(void);

	signals:

		void sgInit(ARB::ALoggerProperties* inProperties);
		void sgInitiated(void);
		void sgWriteToLog(ARB::ALoggerMessageModel inMessage);

	private:

		explicit ALogger(QObject* parent = nullptr);
		virtual ~ALogger(void);
		Q_DISABLE_COPY(ALogger)
};

} // namespace ARB

#endif // ALOGGER_H
