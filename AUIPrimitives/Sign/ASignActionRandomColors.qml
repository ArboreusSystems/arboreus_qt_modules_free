// ----------------------------------------------------------
/*!
	\qmltype
	\brief

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/06/2026 at 15:07:41
	\endlist
*/
// ----------------------------------------------------------

// System includes
import QtQuick;

// Application includes


// Component
Rectangle {

	property var pColors: ["magenta","cyan","yellow"];

	id: oRoot;

	Row {

		id: oElements;
		anchors.fill: parent;
	}

	Component.onCompleted: {

		oRoot.mRegenerate();
	}

	function mRegenerate() {

		oRoot.mClearRow();
		oRoot.mGenerateRow();
	}

	function mClearRow() {

		for (var i = oElements.children.length - 1; i >= 0; i--) {
			oElements.children[i].destroy();
		}
	}

	function mGenerateRow() {

		var oWidthSumm = 0;
		var oCounter = 0;

		while (oWidthSumm < oRoot.width) {

			var oWidth = Math.floor(Math.random() * 2) ? oElements.height : oElements.height / 2.5;
			var oID = "oObject_" + oCounter;

			var oElement = Qt.createQmlObject(
				"import QtQuick;" +
				"Rectangle {" +
				"	id: oObject_" + oCounter + ";" +
				"	height: parent.height;" +
				"	width: " + oWidth +";" +
				"}",
				oElements
			);
			oElement.color = AColors.mGetString(
				oRoot.pColors[Math.floor(Math.random() * oRoot.pColors.length)]
			);

			oWidthSumm += oWidth;
			oCounter += 1;
		}
	}
}
