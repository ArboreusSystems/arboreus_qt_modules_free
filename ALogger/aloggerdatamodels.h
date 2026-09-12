// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 18/10/2025 at 10:38:37
	\endlist
*/
// ----------------------------------------------------------

#ifndef ALOGGERDATAMODELS_H
#define ALOGGERDATAMODELS_H

// Precompiled includes
#include <alogger_pch.h>

// System includes

// Application includes
#include <aloggerdefinitions.h>

// Constants and defintions

// Classes
namespace ARB {

class ALoggerAgent;

} // namespace ARB

// Namespace
namespace ARB {

// Class definition
class ALoggerMessageModel {

	public:

		unsigned long long Time = 0;
		QtMsgType Type = QtMsgType::QtDebugMsg;
		const char* Author = _A_LOGGER_DEFAULT_STRING_UNDEFINED;
		QByteArray ThreadID = {};
		QByteArray Message = {};
		const char* Function = "NoFunction";
		const char* File = "NoFile";
		int Line = 0;

		explicit ALoggerMessageModel(void) {}
		virtual ~ALoggerMessageModel(void) {}
};

} // namespace ARB

Q_DECLARE_METATYPE(ARB::ALoggerMessageModel)


// Namespace
namespace ARB {

// Class definition
class ALoggerProperties {

	public:

		QString PathLoggerDB = "NoPathLoggerDB";
		QString PathLoggerFile = "PathLoggerFile";
		QObject* ConfigObject = nullptr;
		ALoggerAgent* Agent = nullptr;

		explicit ALoggerProperties(void) {}
		virtual ~ALoggerProperties(void) {}
};

} // namespace ARB

Q_DECLARE_METATYPE(ARB::ALoggerProperties)

#endif // ALOGGERDATAMODELS_H
