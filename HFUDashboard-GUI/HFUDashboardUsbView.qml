import QtQuick 2.7

Item {
    id: usbView
    width: 800
    height: 600
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    property var musicFilesList: []

    Connections {
        target: connector
        onAudioWheelTurnedLeft: {
            audioWheelTurnedLeft()
        }
        onAudioWheelTurnedRight: {
            audioWheelTurnedRight()
        }
        onMusicPlayButtonPressed: {
            playButton.source = playButton.pausePath
        }
        onMusicPauseButtonPressed: {
            playButton.source = playButton.playPath
        }
        onMusicBackwardButtonPressed: {
            backwardButton.source = backwardButton.backwardButtonPressedPath
        }
        onMusicForwardButtonPressed: {
            forwardButton.source = forwardButton.forwardButtonPressedPath
        }
        onMusicWheelDirectionNormal: {
            backwardButton.source = backwardButton.backwardButtonPath
            forwardButton.source = forwardButton.forwardButtonPath
        }
        onSendNewMusicList: {
            setNewFileList(filesStructure)
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
        source: musicState.coverPath
    }

    Item {
        id: usbViewButtons
        width: 500
        height: 100
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: 190
        anchors.leftMargin: -100

        Text {
            id: title
            width: parent.width - 100
            height: 20
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 50
            horizontalAlignment:  Text.AlignHCenter
            text: musicState.title
            font.pointSize: 16
            color: "white"
            clip: true
        }

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
                    progressBar.fullProgressBar.width =
                            (progressBar.fullProgressBar.parent.width / musicState.titleDuration) * musicState.currentPlayTimeSeconds
                    progressBar.progressButton.anchors.leftMargin =
                            (progressBar.progressButton.parent.width / musicState.titleDuration) * musicState.currentPlayTimeSeconds - 7
                }
            }
        }

        Image {
            id: backwardButton
            property string backwardButtonPath: "bilder/UsbView/BackwardButton.png"
            property string backwardButtonPressedPath: "bilder/UsbView/BackwardButtonPressed.png"
            width: 40
            height: 40
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 50
            source: backwardButtonPath
        }

        Image {
            id: playButton
            property string playPath: "bilder/UsbView/PlayButton.png"
            property string pausePath: "bilder/UsbView/PauseButton.png"
            width: 40
            height: 40
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            source: playPath
        }

        Image {
            id: forwardButton
            property string forwardButtonPath: "bilder/UsbView/ForwardButton.png"
            property string forwardButtonPressedPath: "bilder/UsbView/ForwardButtonPressed.png"
            width: 40
            height: 40
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.rightMargin: 50
            source: forwardButtonPath
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
                width: parent.width; height: 32;
                Row {
                    Image {
                        height: 32
                        width: 32
                        source: image
                    }
                    // if its a musicTitle
                    Column {
                        visible: interpreter != ""
                        Text {
                            text: "<b>Title:</b> " + title
                            font.pointSize: 12
                        }
                        Text {
                            text: "<b>Interpret:</b> " + "<i>" + interpreter + "</i>"
                            font.pointSize: 12
                        }
                    }
                    // if its a directory
                    Text {
                            visible: interpreter == ""
                            text: "<b>DirName:</b> " + title
                            font.pointSize: 12
                            anchors.verticalCenter: parent.verticalCenter
                    }
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

    function setMusicTitleCache() {
        if (usbView.musicFilesList.length > 0) {
            musicState.titleCache = usbView.musicFilesList[0][musicList.currentIndex];
            musicState.tilteDurationCache = usbView.musicFilesList[2][musicList.currentIndex];
            musicState.coverPathCache = "image://cover/" + usbView.musicFilesList[3][musicList.currentIndex];
        }
    }


    function audioWheelTurnedLeft() {
        if (musicList.currentIndex > 0) {
            musicList.currentIndex--;
        }
        setMusicTitleCache();
    }

    function audioWheelTurnedRight() {
        if (musicList.currentIndex < musicList.count-1) {
            musicList.currentIndex++;
        }
        setMusicTitleCache();
    }

    function setNewFileList(filesStructure) {
        musicState.titleCache = filesStructure[0][0];
        musicState.tilteDurationCache = filesStructure[2][0];
        musicState.coverPathCache = "image://cover/" + filesStructure[3][0];
        usbView.musicFilesList = filesStructure;
        musicList.model.clear();
        for (var i=0; i < filesStructure[0].length; i++) {
            appendEntry(filesStructure[0][i], filesStructure[1][i], filesStructure[3][i])
        }
    }

    function appendEntry(titleName, artistName, coverId) {
        var coverPath = "image://cover/" + coverId;
        if (artistName === "")
            musicList.model.append({ "title": titleName,
                                   "interpreter": artistName,
                                   "image": coverPath})
        else
            musicList.model.append({ "title": titleName,
                               "interpreter": artistName,
                               "image": coverPath})
    }
}

