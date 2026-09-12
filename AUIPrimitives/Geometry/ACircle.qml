// ----------------------------------------------------------
/*!
	\qmltype
	\brief

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 06/04/2026 at 21:57:48
	\endlist
*/
// ----------------------------------------------------------

// System includes
import QtQuick;

// Application includes


// Component
Rectangle {

	property int pSize: 10;

	id: oRoot;
	width: oRoot.pSize;
	height: oRoot.pSize;
	radius: oRoot.width / 2;
}
