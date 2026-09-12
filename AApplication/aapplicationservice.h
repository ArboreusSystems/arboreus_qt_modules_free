// ----------------------------------------------------------
/*!
	\headerfile AApplicationService
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/10/2025 at 18:05:20
	\endlist
*/
// ----------------------------------------------------------
#ifndef AAPPLICATIONSERVICE_H
#define AAPPLICATIONSERVICE_H

// Precompiled includes
#include <aapplication_pch.h>

// System includes

// Application includes
#include <aloggerdefinitions.h>
#include <athreadservicetemplate.h>

// Namesapces

// Constants and definitions

// Namespace
namespace ARB {

// Class definitions
class AApplicationService : public AThreadServiceTemplate {

	Q_OBJECT

	public:

		explicit AApplicationService(QObject* parent = nullptr);
		virtual ~AApplicationService(void);

	public slots:

		void slInit(void);

	signals:

		void sgInitiated(void);
};

} // namespace ARB

#endif // AAPPLICATIONSERVICE_H
