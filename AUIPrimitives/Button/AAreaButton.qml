// ----------------------------------------------------------
/*!
	\qmltype
	\brief

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 24/04/2026 at 22:29:27
	\endlist
*/
// ----------------------------------------------------------

// System includes
import QtQuick;

// Application includes
import UIDataModifierMobile;


// Component
Rectangle {

	required property string pID;
	property bool pDeclareAction: true;
	property alias pMouseArea: oMouseArea;

	id: oRoot;
	objectName: oRoot.pID;
	color: "magenta";

	MouseArea {

		id: oMouseArea;
		anchors.fill: parent;

		onClicked: {

			if (oRoot.pDeclareAction) AApplication.mDeclareAction([oRoot.pID,"onClicked",0]);
		}
	}
}
