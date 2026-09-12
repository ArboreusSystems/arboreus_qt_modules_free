// ----------------------------------------------------------
/*!
	\headerfile AUIHandler
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 08/01/2026 at 19:30:41
	\endlist
*/
// ----------------------------------------------------------

#ifndef AUIHANDLER_H
#define AUIHANDLER_H

// Precompiled includes
#include <auihandler_pch.h>

// System includes

// Application includes
#include <alogger.h>
#include <auihandlerconfig.h>
#include <auiconfig.h>
#include <afonts.h>
#include <acolors.h>

// Namespace
namespace ARB {

// Class definitions
class AUIHandler : public QObject {

	Q_OBJECT

	public:

		AFonts* pFonts = nullptr;
		AColors* pColors = nullptr;
		AUIConfig* pUIConfig = nullptr;

		explicit AUIHandler(QObject* parent = nullptr);
		virtual ~AUIHandler(void);
		Q_DISABLE_COPY(AUIHandler)

		void mInit(QObject* inConfig);

	signals:

		void sgInitiated(void);

	private:

		AUIHandlerConfig* pConfig = nullptr;
};

} // namespace ARB

#endif // AUIHANDLER_H
