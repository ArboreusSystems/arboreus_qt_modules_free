// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 15/10/2025 at 17:24:52
	\endlist
*/
// ----------------------------------------------------------

#ifndef ATHREADAGENTTEMPLATE_H
#define ATHREADAGENTTEMPLATE_H

// Precompiled includes
#include <atemplates_pch.h>

// System includes

// Application includes

// Constants and defintions

// Namespace
namespace ARB {

class AThreadAgentTemplate : public QObject {

	Q_OBJECT

	public:

		explicit AThreadAgentTemplate(QObject* parent = nullptr): QObject(parent) {}
		virtual ~AThreadAgentTemplate(void) {}

	public slots:

		virtual void slRun(void) = 0;

	signals:

		void sgFinished(void);
};

} // namespace ARB

#endif // ATHREADAGENTTEMPLATE_H
