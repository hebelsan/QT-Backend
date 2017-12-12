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
                if (volumeAdjuster.anchors.rightMargin + volumeBar.width / 20 < volumeBar.width)
                    volumeAdjuster.anchors.rightMargin += volumeBar.width / 20
            }
            onVolumeDownFrameReceived: {
                canEventSink.setShowVolume(true);
                if (mainView.visible && canEventSink.activeLeftView != media) {
                    canEventSink.setLeftViewToMedia();
                    connector.menuStateFrameReceived();
                }
                if (volumeAdjuster.anchors.rightMargin - volumeBar.width / 20 > 0)
                    volumeAdjuster.anchors.rightMargin -= volumeBar.width / 20
            }
            onMusicPlayButtonPressed: {
                if (mainView.visible && canEventSink.activeLeftView != media) {
                    canEventSink.setLeftViewToMedia();
                    connector.menuStateFrameReceived();
                }
                if (!canEventSink.isPlaying) {
                    canEventSink.isPlaying = !canEventSink.isPlaying
                    musicPlayButton.source = musicPlayButton.playPressedPath
                    playButtonTimer.start()
                } else {
                    canEventSink.isPlaying = !canEventSink.isPlaying
                    musicPlayButton.source = musicPlayButton.pausedPressedPath
                    pauseButtonTimer.start()
                }
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
            property string playNormalPath: "bilder/MusicPlay.png"
            property string playPressedPath: "bilder/MusicPlayPressed.png"
            property string pausedNormalPath: "bilder/MusicPause.png"
            property string pausedPressedPath: "bilder/MusicPausePressed.png"
            property bool pressed: false
            width: 40
            height: 40
            source: playNormalPath
            anchors.horizontalCenter: mediaWindow.horizontalCenter
            anchors.bottom: mediaWindow.bottom
            anchors.bottomMargin: 120

            transitions: Transition {
                NumberAnimation { property: "source"; duration: 200 }
            }

            Timer {
                id: playButtonTimer
                interval: 100; running: false; repeat: false
                onTriggered: musicPlayButton.source = musicPlayButton.pausedNormalPath;
            }

            Timer {
                id: pauseButtonTimer
                interval: 100; running: false; repeat: false
                onTriggered: musicPlayButton.source = musicPlayButton.playNormalPath;
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
            anchors.right: parent.right
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
