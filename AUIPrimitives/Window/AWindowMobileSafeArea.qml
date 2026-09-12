// ----------------------------------------------------------
/*!
	\qmltype
	\brief

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 31/01/2026 at 07:21:07
	\endlist
*/
// ----------------------------------------------------------

// System includes
import QtQuick;
import QtQuick.Controls;
import QtQuick.Window;

// Application includes


// Component
Window {

	signal sgKeyboardVisible(bool inVisibility);

	required property string pObjectName;
	property string pTitle: qsTrId("A.MainWindow.Title");
	property string pColorBackgroundScreen: "navajowhite";
	property string pColorBackgroundContent: "steelblue";
	property bool pBottomInput: false;
	property alias pContentWrapper: oContentWrapper;
	property bool pWindowMaximized: false;

	id: oRoot;
	objectName: oRoot.pObjectName;
	visible: true;
	flags: Qt.Window | Qt.MaximizeUsingFullscreenGeometryHint;
	title: oRoot.pTitle;
	color: oRoot.pColorBackgroundScreen;

	onVisibilityChanged: {

		if (Qt.platform.os === "android") {
			if (oRoot.visibility === Window.Hidden || oRoot.visibility === Window.Minimized) {
				oRoot.pWindowMaximized = (oRoot.visibility === Window.Maximized)
			} else if (oRoot.visibility === Window.FullScreen) {
				if (!oRoot.pWindowMaximized) {
					oRoot.visibility = Window.Windowed
				} else {
					oRoot.visibility = Window.Maximized
				}
			}
		}
	}

	Item {

		id: oWindowWrapper;
		anchors.top: parent.top;
		anchors.topMargin: oRoot.SafeArea.margins.top;
		anchors.bottom: parent.bottom;
		anchors.bottomMargin: oRoot.SafeArea.margins.bottom;
		anchors.left: parent.left;
		anchors.leftMargin: oRoot.SafeArea.margins.left;
		anchors.right: parent.right;
		anchors.rightMargin: oRoot.SafeArea.margins.right;

		Rectangle {

			id: oContentWrapper;
			anchors.top: parent.top;
			anchors.bottom: parent.bottom;
			anchors.left: parent.left;
			anchors.right: parent.right;
			color: oRoot.pColorBackgroundContent;
		}
	}

	Connections {

		target: ATranslator;
		function onSgLocaleChanged(inLocale) {

			oRoot.pTitle = qsTrId("A.MainWindow.Title");
		}
	}

	Connections {

		target: Qt.inputMethod;
		function onKeyboardRectangleChanged() {

			oTimerResize.restart();
		}
	}

	Timer {

		id: oTimerResize;
		interval: 150;
		repeat: false;
		running: false;

		onTriggered: {

			var oVisible = Qt.inputMethod.visible;

			if (Qt.platform.os === "ios") {
				oRoot.mResizeIOS(oVisible);
			} else if (Qt.platform.os === "android") {
				oRoot.mResizeAndroid(oVisible);
			} else {
				console.log("Not mobile platform");
			}
		}
	}

	function mResize() {

		oTimerResize.restart();
	}

	function mResizeIOS(inVisible) {

		if (inVisible) {
			oWindowWrapper.anchors.bottomMargin = AKeyboard.mHeight();
			oWindowWrapper.anchors.topMargin = oRoot.SafeArea.margins.top;
		} else {
			oWindowWrapper.anchors.bottomMargin = oRoot.SafeArea.margins.bottom;
			oWindowWrapper.anchors.topMargin = oRoot.SafeArea.margins.top;
		}

		oRoot.sgKeyboardVisible(inVisible);
	}

	function mResizeAndroid(inVisible) {

		var oOffsetY = Qt.inputMethod.keyboardRectangle.y / Screen.devicePixelRatio;
		if (inVisible && oOffsetY > 0) {
			oWindowWrapper.anchors.bottomMargin = AKeyboard.mHeight();
			oWindowWrapper.anchors.topMargin = oRoot.SafeArea.margins.top;
		} else {
			oWindowWrapper.anchors.bottomMargin = oRoot.SafeArea.margins.bottom;
			oWindowWrapper.anchors.topMargin = oRoot.SafeArea.margins.top;
		}

		oRoot.sgKeyboardVisible(inVisible);
	}
}
