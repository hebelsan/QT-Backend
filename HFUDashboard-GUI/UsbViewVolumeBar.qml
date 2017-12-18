import QtQuick 2.7

Item {
    id: volumeBar2
    width: 15
    height: 250
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.topMargin: 220
    anchors.leftMargin: -300

    Connections {
        target: connector
        onVolumeDownFrameReceived: {
            if (redVolumeBar.height - redVolumeBar.height / 20 > 0) {
                redVolumeBar.height -= redVolumeBar.maxHeight / 20;
            }
        }
        onVolumeUpFrameReceived: {
            if (redVolumeBar.height + redVolumeBar.height / 20 < redVolumeBar.maxHeight) {
                redVolumeBar.height += redVolumeBar.maxHeight / 20
            }
        }
    }

    Image {
        width: 15
        height: 250
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        source: "bilder/UsbView/Volumebalken.png"
    }

    Image {
        id: redVolumeBar
        property real maxHeight: 250
        width: 15
        height: 250
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        source: "bilder/UsbView/Volumebalken_rot.png"
    }
}
