import QtQuick 2.7

Item {
    id: volumeBar2
    width: 15
    height: 250
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.topMargin: 220
    anchors.leftMargin: -300
    visible: false

    Connections {
        target: connector
        onVolumeDownFrameReceived: {
            showVolume()
            if (redVolumeBar.height - redVolumeBar.height / 20 > 0) {
                redVolumeBar.height -= redVolumeBar.maxHeight / 20;
            }
            setSpeaker()
        }
        onVolumeUpFrameReceived: {
            showVolume()
            if (redVolumeBar.height + redVolumeBar.height / 20 < redVolumeBar.maxHeight) {
                redVolumeBar.height += redVolumeBar.maxHeight / 20
            }
            setSpeaker()
        }
    }

    Image {
        width: 15
        height: 250
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: 20
        source: "bilder/UsbView/Volumebalken.png"
    }

    Image {
        id: redVolumeBar
        property real maxHeight: 250
        width: 15
        height: 250
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: 20
        source: "bilder/UsbView/Volumebalken_rot.png"
    }


    Image {
        id: speaker
        property string pathFull: "bilder/UsbView/speaker/speakerFull.png"
        property string pathMiddle: "bilder/UsbView/speaker/speakerHalf.png"
        property string pathLow: "bilder/UsbView/speaker/speakerLow.png"
        property string pathQuiet: "bilder/UsbView/speaker/speakerQuiet.png"
        width: 40
        height: 40
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: - 30
        anchors.leftMargin: - 7
        source: pathFull
    }

    Timer {
        id: showVolumeTimer
        interval: 3500; running: false; repeat: false
        onTriggered: volumeBar2.visible = false;
    }

    function setSpeaker() {
        if (redVolumeBar.height >= redVolumeBar.maxHeight - redVolumeBar.maxHeight / 20)
            speaker.source = speaker.pathFull
        else if (redVolumeBar.height <= 1)
            speaker.source = speaker.pathQuiet
        else if (redVolumeBar.height <= redVolumeBar.maxHeight / 3)
            speaker.source = speaker.pathLow
        else if (redVolumeBar.height <= redVolumeBar.maxHeight - redVolumeBar.maxHeight / 20)
            speaker.source = speaker.pathMiddle
    }

    function showVolume() {
        volumeBar2.visible = true
        showVolumeTimer.start()
    }
}
