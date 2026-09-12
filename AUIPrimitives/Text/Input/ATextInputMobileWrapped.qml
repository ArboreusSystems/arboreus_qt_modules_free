// ----------------------------------------------------------
/*!
	\qmltype
	\brief

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 27/05/2026 at 11:34:24
	\endlist
*/
// ----------------------------------------------------------

// System includes
import QtQuick;
import QtQuick.Controls;

// Application includes
import AQML;


// Component
Rectangle {

	property alias pTextInput: oTextInput;

	id: oRoot;
	color: "magenta";

	ATextInputMobile {

		id: oTextInput;

		anchors.verticalCenter: parent.verticalCenter;
		anchors.left: parent.left;
		anchors.right: parent.right;
		color: "white";
		verticalAlignment: TextInput.AlignVCenter;
		clip: true;

		Component.onCompleted: {

			oTextInput.cursorPosition = 0;
		}

		onActiveFocusChanged: {

			if (oTextInput.activeFocus) {
				oTextInput.cursorPosition = oTextInput.text.length;
			} else {
				oTextInput.cursorPosition = 0;
			}
		}
	}
}

