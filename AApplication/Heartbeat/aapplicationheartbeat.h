// ----------------------------------------------------------
/*!
	\headerfile AApplicationHeartBeat
	\title
	\brief Template file wizard/classes/cpp/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/10/2025 at 18:12:48
	\endlist
*/
// ----------------------------------------------------------
#ifndef AAPPLICATIONHEARTBEAT_H
#define AAPPLICATIONHEARTBEAT_H

// Precompiled includes
#include <aapplication_pch.h>

// System includes

// Application includes
#include <aloggerdefinitions.h>

// Constants and definitions

// Namesapces
namespace ARB {

// Class definitions
class AApplicationHeartBeat : public QObject {

	Q_OBJECT

	public:

		explicit AApplicationHeartBeat(QObject* parent = nullptr);
		virtual ~AApplicationHeartBeat(void);
};

} // namespace ARB

#endif // AAPPLICATIONHEARTBEAT_H
