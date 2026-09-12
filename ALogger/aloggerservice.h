// ----------------------------------------------------------
/*!
	\headerfile ALoggerService
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 15/10/2025 at 23:16:22
	\endlist
*/
// ----------------------------------------------------------
#ifndef ALOGGERSERVICE_H
#define ALOGGERSERVICE_H

// Precompiled includes
#include <alogger_pch.h>

// System includes

// Application includes
#include <athreadservicetemplate.h>
#include <aloggerdatamodels.h>
#include <aloggeragent.h>

// Constants and definitions

// Namesapces
namespace ARB {

// Class definitions
class ALoggerService : public AThreadServiceTemplate {

	Q_OBJECT

	public:

		explicit ALoggerService(QObject* parent = nullptr);
		virtual ~ALoggerService(void);

	public slots:

		void slInit(ARB::ALoggerProperties* inProperties);
		void slInitiated(void);
		void slWriteToLog(ARB::ALoggerMessageModel inModel);

	signals:

		void sgInit(ARB::ALoggerProperties* inProperties);
		void sgInitiated(void);

	private:

		ALoggerAgent* pAgent = nullptr;
};

} // namespace ARB

#endif // ALOGGERSERVICE_H
