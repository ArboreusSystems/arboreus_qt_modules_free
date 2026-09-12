// ----------------------------------------------------------
/*!
    \qmltype
    \brief

    \list
    \li @notice Template file classes/file.h
    \li @copyright Arboreus (http://arboreus.systems)
    \li @author Alexandr Kirilov (http://alexandr.kirilov.me)
    \li @created 03/03/2026 at 19:32:45
    \endlist
*/
// ----------------------------------------------------------

// System includes
import QtQuick;
import QtQuick.Controls;

// Application includes
import UIDataModifierMobile;


// Component
Button {

    required property string pId;
    property string pColor: "magenta";
    property int pRadius: 0;
    property bool pDeclareAction: true;

    id: oRoot;
    objectName: pId;

    background: Rectangle {

        color: oRoot.pColor;
        radius: oRoot.pRadius;
    }

    onClicked: {

        if (oRoot.pDeclareAction) AApplication.mActionAppeared([pId,"onClicked",0]);
	}
}
