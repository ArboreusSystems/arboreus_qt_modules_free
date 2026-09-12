// ----------------------------------------------------------
/*!
	\qmltype
	\brief

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 12/08/2026 at 20:20:35
	\endlist
*/
// ----------------------------------------------------------

// System includes
import QtQuick;
import QtQuick.VectorImage;

// Application includes


// Component
Item {

	property real pScale: 1.0;
	property alias pSource: oVectorImage.source;

	id: oRoot;
	width: oVectorImage.implicitWidth * oRoot.pScale;
	height: oVectorImage.implicitHeight * oRoot.pScale;

	VectorImage {

		id: oVectorImage;
		height: parent.height;
		width: parent.width;
		fillMode: Image.PreserveAspectFit;
	}
}
