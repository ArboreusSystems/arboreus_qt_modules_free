// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 15/10/2025 at 17:23:43
	\endlist
*/
// ----------------------------------------------------------

#ifndef ATHREADOBJECTCONTROLLERTEMPLATE_H
#define ATHREADOBJECTCONTROLLERTEMPLATE_H

// Precompiled includes
#include <atemplates_pch.h>

// System includes

// Application includes

// Constants and defintions

// Namespace
namespace ARB {

class AThreadObjectControllerTemplate : public QObject {

	Q_OBJECT

	public:

		explicit AThreadObjectControllerTemplate(QObject* parent = nullptr): QObject(parent) {}
		virtual ~AThreadObjectControllerTemplate(void) {}

	signals:

		void sgRun(void);
};

} // namespace ARB


#endif // ATHREADOBJECTCONTROLLERTEMPLATE_H
