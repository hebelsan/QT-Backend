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
                musicState.setShowVolume(true);
                if (volumeAdjuster.anchors.rightMargin - volumeBar.width / 20 > 0)
                    volumeAdjuster.anchors.rightMargin -= volumeBar.width / 20
            }
            onVolumeDownFrameReceived: {
                musicState.setShowVolume(true);
                if (volumeAdjuster.anchors.rightMargin + volumeBar.width / 20 < volumeBar.width)
                    volumeAdjuster.anchors.rightMargin += volumeBar.width / 20
            }
            onMusicPlayButtonPressed: {
                if (!musicState.isPlaying) {
                    musicState.isPlaying = !musicState.isPlaying
                    musicPlayButton.source = musicPlayButton.playPressedPath
                    playButtonTimer.start()
                } else {
                    musicState.isPlaying = !musicState.isPlaying
                    musicPlayButton.source = musicPlayButton.pausedPressedPath
                    pauseButtonTimer.start()
                }
                if (playTimeTest.running)
                    playTimeTest.stop();
                else
                    playTimeTest.start();
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
        x: 185
        y: 50
        width: 250
        height: parent.height - 50

        Rectangle {
            width: parent.width - 60
            height: 160
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 30
            border.color: "red"
            border.width: 3
        }

        Text {
            width: parent.width
            height: 30
            anchors.top: parent.top
            anchors.topMargin: 180
            horizontalAlignment:  Text.AlignHCenter
            text: musicState.title
            font.pointSize: 20
            color: "white"
        }

        MusicTitleProgressBar {
            id: progressBar
            width: parent.width
            anchors.top: parent.top
            anchors.topMargin: 220
            anchors.left: parent.left

            Timer {
                id: playTimeTest
                interval: 1000; running: false; repeat: true
                onTriggered: musicState.movePlayTime(fullProgressBar, progressButton);
            }
        }

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
            State { when: musicState.showVolume;
                PropertyChanges { target: volume; opacity: 1.0 }
                PropertyChanges { target: volumeTimer; running: true }
            },
            State { when: !musicState.showVolume;
                PropertyChanges { target: volume; opacity: 0.5 }
            }
        ]
        transitions: Transition {
            NumberAnimation { property: "opacity"; duration: 700 }
        }

        Timer {
            id: volumeTimer
            interval: 5000; running: false; repeat: false
            onTriggered: musicState.setShowVolume(false);
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
