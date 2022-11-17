import QtQuick 2.12
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15
import QtMultimedia 5.8
 
Rectangle {
    property bool maximized: mainWindow.isMaximized || mainWindow.isFullScreen

    id: window
    anchors.fill: parent
    color: 'black'

    VideoOutput {
        id: videoOutput

        property double  aimedRatio     : sourceRect.height/sourceRect.width
        property double  marginBottom   : window.maximized ? 0 : buttons.height

        property double  availableWidth  : parent.width
        property double  availableHeight : parent.height - marginBottom

        property bool    parentIsLarge   : parentRatio > aimedRatio

        property double  parentRatio     : availableHeight / availableWidth

        height : parentIsLarge ? availableWidth * aimedRatio :  availableHeight
        width  : parentIsLarge ? availableWidth     :  availableHeight / aimedRatio

        anchors.horizontalCenter: parent.horizontalCenter

        source: videoFrameProvider

        MouseArea {
            anchors.fill: parent

            hoverEnabled: true

            onPressed: function (mouse) {
                console.log("pressed")
                device.onPressed(mouse.x,
                                 mouse.y,
                                 mouse.button,
                                 mouse.buttons,
                                 mouse.modifiers,
                                 Qt.size(videoOutput.sourceRect.width, videoOutput.sourceRect.height),
                                 Qt.size(videoOutput.contentRect.width, videoOutput.contentRect.height))
            }

            onReleased: function (mouse) {
                console.log("released")
                device.onReleased(mouse.x,
                                  mouse.y,
                                  mouse.button,
                                  mouse.buttons,
                                  mouse.modifiers,
                                  Qt.size(videoOutput.sourceRect.width, videoOutput.sourceRect.height),
                                  Qt.size(videoOutput.contentRect.width, videoOutput.contentRect.height))
            }

            onPositionChanged: {
                console.log("[video content rect]", videoOutput.contentRect)
                console.log("[source rect]", videoOutput.sourceRect)
                console.log("moved!", mouse.x, mouse.y)

                device.onMouseMove(mouse.x,
                                   mouse.y,
                                   mouse.button,
                                   mouse.buttons,
                                   mouse.modifiers,
                                   Qt.size(videoOutput.sourceRect.width, videoOutput.sourceRect.height),
                                   Qt.size(videoOutput.contentRect.width, videoOutput.contentRect.height))
            }
        }
    }

    Rectangle {
        id: buttons

        width: window.maximized ? 56 : parent.width
        height: window.maximized ? parent.height : 56
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        GridLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            flow:  window.maximized ? GridLayout.TopToBottom : GridLayout.LeftToRight

            // spacing: 10

            RoundButton {
                width: 36
                height: 36
                radius: 8
                icon.source: "qrc:///icons/back.svg"
                icon.width: 16
                icon.height: 16
                onClicked: device.onBackButtonClicked()
            }

            RoundButton {
                width: 36
                height: 36
                radius: 8
                icon.source: "qrc:///icons/overview.svg"
                icon.width: 16
                icon.height: 16
                onClicked: device.onOverviewButtonClicked()
            }

            RoundButton {
                width: 36
                height: 36
                radius: 8
                icon.source: "qrc:///icons/home.svg"
                icon.width: 16
                icon.height: 16
                onClicked: device.onHomeButtonClicked()
            }

            RoundButton {
                width: 36
                height: 36
                radius: 8
                icon.source: "qrc:///icons/switch_screen.svg"
                icon.width: 16
                icon.height: 16
                onClicked: device.onSwitchScreenButtonClicked()
            }

        }
    }
}