// ----------------------------------------------------------
/*!
	\headerfile %{CN}
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 18/10/2025 at 10:33:13
	\endlist
*/
// ----------------------------------------------------------

#ifndef ALOGGERDEFINITIONS_H
#define ALOGGERDEFINITIONS_H

// Precompiled includes
#include <alogger_pch.h>

// System includes

// Application includes

// Constants and defintions
#define _A_LOGGER_DEFAULT_STRING_DEBUG "DBG"
#define _A_LOGGER_DEFAULT_STRING_INFO "INF"
#define _A_LOGGER_DEFAULT_STRING_WARNING "WRN"
#define _A_LOGGER_DEFAULT_STRING_CRITICAL "CRT"
#define _A_LOGGER_DEFAULT_STRING_FATAL "FTL"
#define _A_LOGGER_DEFAULT_STRING_UNDEFINED "NDF"
#define _A_LOGGER_DEFAULT_STRING_SYSTEM "SYS"
#define _A_LOGGER_DEFAULT_STRING_USER "USR"
#define _A_LOGGER_DEFAULT_STRING_NETWORK "NET"

#define _A_DEBUG qDebug()
#define _A_USER qDebug() << _A_LOGGER_DEFAULT_STRING_USER
#define _A_INFO qInfo()
#define _A_WARNING qWarning()
#define _A_CRITICAL qCritical()
#define _A_FATAL(inMessage) qFatal(inMessage)

#endif // ALOGGERDEFINITIONS_H
