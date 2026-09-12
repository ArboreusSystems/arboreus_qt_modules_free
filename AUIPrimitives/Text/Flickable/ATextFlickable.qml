// ----------------------------------------------------------
/*!
	\qmltype
	\brief

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 27/06/2026 at 21:42:28
	\endlist
*/
// ----------------------------------------------------------

// System includes
import QtQuick;
import QtQuick.Controls;

// Application includes


// Component
Rectangle {

	property alias pFlickable: oFlickable;
	property alias pText: oText;

	id: oRoot;
	color: "magenta";

	Flickable {

		id: oFlickable;
		anchors.fill: parent;
		contentWidth: oFlickable.width;
		contentHeight: Math.max(oText.implicitHeight,oFlickable.height)
		flickableDirection: Flickable.VerticalFlick;
		clip: true;

		Text {

			id: oText;
			width: oFlickable.width;
			anchors.horizontalCenter: parent.horizontalCenter;
			wrapMode: Text.WordWrap;
			text: "Default text for ATextFlickable";
			y: Math.max(0,oFlickable.height - oText.height);
		}
	}
}
