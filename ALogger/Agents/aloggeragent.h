// ----------------------------------------------------------
/*!
	\headerfile ALoggerAgent
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 19/10/2025 at 15:44:29
	\endlist
*/
// ----------------------------------------------------------
#ifndef ALOGGERAGENT_H
#define ALOGGERAGENT_H

// Precompiled includes
#include <alogger_pch.h>

// System includes

// Application includes
#include <aloggerdatamodels.h>

// Constants and definitions

// Namesapces
namespace ARB {

// Class definitions
class ALoggerAgent : public QObject {

	Q_OBJECT

	public:

		explicit ALoggerAgent(QObject* parent = nullptr);
		virtual ~ALoggerAgent(void);

		virtual void mWriteToLog(ALoggerMessageModel inMessage);
		static void mOnStopping(
			QtMsgType inType,
			const QMessageLogContext& inContext,
			const QString& inMessage
		);
		static void mWriteToConsole(ALoggerMessageModel inModel);

	public slots:

		virtual void slInit(ARB::ALoggerProperties* inProperties);

	signals:

		void sgInitiated(void);
};

} // namespace ARB

#endif // ALOGGERAGENT_H
