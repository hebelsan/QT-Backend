import QtQuick 2.7
import QtQuick.Controls.Styles 1.4

/**
  * Implements media on the left side
  *
  * Right now its just an image with no interactions
  *
  */
Item{
    id: hfuMediaLeft
    property alias hfuMediaLeft: hfuMediaLeft

    NumberAnimation on opacity {
        id: createAnimation
        from: 0
        to:1
        duration: 500
    }
    Component.onCompleted: createAnimation.start()
    onParentChanged: createAnimation.start()


    /**
      * Slots for receiving signals from the Connector class
      *
      */
    Item {
        Connections {
            target: connector
            onVolumeUpFrameReceived: {
                canEventSink.setShowVolume(true);
                if (mainView.visible && canEventSink.activeLeftView != media) {
                    canEventSink.setLeftViewToMedia();
                    connector.menuStateFrameReceived();
                }
                if (volumeAdjuster.anchors.leftMargin + volumeBar.width / 30 < volumeBar.width)
                    volumeAdjuster.anchors.leftMargin += volumeBar.width / 30
            }
            onVolumeDownFrameReceived: {
                canEventSink.setShowVolume(true);
                if (mainView.visible && canEventSink.activeLeftView != media) {
                    canEventSink.setLeftViewToMedia();
                    connector.menuStateFrameReceived();
                }
                if (volumeAdjuster.anchors.leftMargin - volumeBar.width / 30 > 0)
                    volumeAdjuster.anchors.leftMargin -= volumeBar.width / 30
            }
            onMusicPlayButtonPressed: {
                if (mainView.visible && canEventSink.activeLeftView != media) {
                    canEventSink.setLeftViewToMedia();
                    connector.menuStateFrameReceived();
                }
                musicPlayButton.source = musicPlayButton.path2
                playButtonTimer.start()
            }
            onMusicBackwardButtonPressed: {
                musicBackwardButton.source = musicBackwardButton.path2
            }
            onMusicForwardButtonPressed: {
                musicForwardButton.source = musicForwardButton.path2
            }
            onMusicWheelDirectionNormal: {
                musicBackwardButton.source = musicBackwardButton.path1
                musicForwardButton.source = musicForwardButton.path1
            }
        }
    }




    Item {
        id: mediaWindow
        x: 190
        y: 25
        width: 250
        height: parent.height - 50

        Image {
            id: musicPlayButton
            property string path1: "bilder/MusicPlay.png"
            property string path2: "bilder/MusicPlayPressed.png"
            property bool pressed: false
            width: 40
            height: 40
            source: path1
            anchors.horizontalCenter: mediaWindow.horizontalCenter
            anchors.bottom: mediaWindow.bottom
            anchors.bottomMargin: 120

            transitions: Transition {
                NumberAnimation { property: "source"; duration: 200 }
            }

            Timer {
                id: playButtonTimer
                interval: 200; running: false; repeat: false
                onTriggered: musicPlayButton.source = musicPlayButton.path1;
            }


            }

        Image {
            id: musicBackwardButton
            property string path1: "bilder/MusicBackward.png"
            property string path2: "bilder/MusicBackwardPressed.png"
            width: 40
            height: 40
            z: 1
            source: path1
            anchors.left: mediaWindow.left
            anchors.bottom: mediaWindow.bottom
            anchors.bottomMargin: 120
            anchors.leftMargin: 10

            transitions: Transition {
                NumberAnimation { property: "source"; duration: 200 }
            }
         }


        Image {
            id: musicForwardButton
            property string path1: "bilder/MusicForward.png"
            property string path2: "bilder/MusicForwardPressed.png"
            width: 40
            height: 40
            z: 1
            source: path1
            anchors.right: mediaWindow.right
            anchors.bottom: mediaWindow.bottom
            anchors.bottomMargin: 120
            anchors.rightMargin: 10

            transitions: Transition {
                NumberAnimation { property: "source"; duration: 200 }
            }
         }
    }

    Item {

        id: volume
        opacity: 0.5
        visible: this.opacity !== 0.5
        x: 190
        width: 250
        height: 120
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 25

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
            id: volumeBar
            width: parent.width - 25
            height: 10
            z: 1
            source: "bilder/MusicVolumebar.png"
            anchors.centerIn: parent
        }

        Image {
            id: volumeAdjuster
            width: 25
            height: 25
            z: 1
            source: "bilder/MusicVolumeAdjuster.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
        }

        Image {
            id: volumePlus
            width: 30
            height: 30
            z: 1
            source: "bilder/MusicVolumeMinus.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.left
        }

        Image {
            id: volumeMinus
            width: 30
            height: 30
            z: 1
            source: "bilder/MusicVolumePlus.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
        }

    }
}
