import QtQuick 2.7

Item {

    id: volume
    opacity: 0.5
    visible: this.opacity !== 0.5

    states: [
        State { when: canEventSink.showVolume;
            PropertyChanges { target: volume; opacity: 1.0 }
            PropertyChanges { target: volumeTimer; running: true }
        },
        State { when: !canEventSink.showVolume;
            PropertyChanges { target: volume; opacity: 0.5 }
        }
    ]
    transitions: Transition {
        NumberAnimation { property: "opacity"; duration: 700 }
    }

    Timer {
        id: volumeTimer
        interval: 5000; running: false; repeat: false
        onTriggered: canEventSink.setShowVolume(false);
    }

    Image {
        id: musicVolumeBar
        width: parent.width - 25
        height: 10
        z: 1
        source: "bilder/MusicVolumebar.png"
        anchors.centerIn: parent
    }

    Image {
        width: 25
        height: 25
        z: 1
        source: "bilder/MusicVolumeAdjuster.png"
        anchors.centerIn: parent
    }

    Image {
        width: 30
        height: 30
        z: 1
        source: "bilder/MusicVolumeMinus.png"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.left
    }

    Image {
        width: 30
        height: 30
        z: 1
        source: "bilder/MusicVolumePlus.png"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.right
    }

}
