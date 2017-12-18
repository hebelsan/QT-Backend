import QtQuick 2.7

Item {
    width: 800
    height: 600
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter

    Connections {
        target: connector
        onAudioWheelTurnedLeft: {
            // musicList.model.clear();
            musicList.model.append({ "titel": "neu",
                                       "interpreter" : "neu" })
            if (usbView.visible) {
                if (musicList.currentIndex > 0) {
                    musicList.currentIndex--;
                }
            }
        }
        onAudioWheelTurnedRight: {
            if (usbView.visible) {
                if (musicList.currentIndex < musicList.count-1) {
                    musicList.currentIndex++;
                }
            }
        }
    }


    UsbViewVolumeBar {
        id: usbViewVolumeBar
        width: 15
        height: 250
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 220
        anchors.leftMargin: -300
    }

    Image {
        id: cover
        width: 100
        height: 100
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: 190
        anchors.leftMargin: -200
        source: "bilder/UsbView/NotenSchluessel.jpg"
    }

    Item {
        id: usbViewButtons
        width: 500
        height: 100
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: 190
        anchors.leftMargin: -100


        MusicTitleProgressBar {
            id: progressBar
            width: parent.width - 100
            anchors.top: parent.top
            anchors.topMargin: 25
            anchors.left: parent.left
            anchors.leftMargin: 50
            Connections {
                target: musicState
                onMusicProgressTimerStarted: {
                    progressBar.fullProgressBar.width +=
                            progressBar.fullProgressBar.parent.width / musicState.titleDuration
                    progressBar.progressButton.anchors.leftMargin +=
                            progressBar.progressButton.parent.width / musicState.titleDuration
                }
            }
        }

        Image {
            id: backwardButton
            width: 40
            height: 40
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 50
            source: "bilder/UsbView/BackwardButton.png"
        }

        Image {
            id: playButton
            width: 40
            height: 40
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            source: "bilder/UsbView/PlayButton.png"
        }

        Image {
            id: forwardButton
            width: 40
            height: 40
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.rightMargin: 50
            source: "bilder/UsbView/ForwardButton.png"
        }
    }

    Image {
        id: rahmen
        visible: true
        width: 625
        height: 340
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 170
        anchors.leftMargin: -253
        source: "bilder/UsbView/UsbRahmen.png"
    }

    Rectangle {
        id: titlListRec
        width: 580
        height: 280
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 200
        anchors.leftMargin: -230
        border.color: "red"
        border.width: 1

        Component {
            id: musicDelegate
            Item {
                width: parent.width; height: 30;
                Column {
                    Text { text: '<b>Titel:</b> ' + titel }
                    Text { text: '<b>Interpreter:</b> ' + interpreter }
                }
            }
        }

        Component {
            id: highlight
            Rectangle {
                color: "red"
                radius: 5
            }
        }

        ListView {
            anchors.fill: parent
            id: musicList
            model: MusicListModel {}
            delegate: musicDelegate
            highlight: highlight
            focus: true
            highlightFollowsCurrentItem: true
            clip: true
        }
    }


}

