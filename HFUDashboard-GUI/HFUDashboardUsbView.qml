import QtQuick 2.7

Item {
    width: 800
    height: 600
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter

    Connections {
        target: connector
        onAudioWheelTurnedLeft: {
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

//    Rectangle {
//        id: test2
//        width: 600
//        height: 280
//        anchors.top: parent.top
//        anchors.left: parent.left
//        anchors.topMargin: 200
//        anchors.leftMargin: -200
//        border.color: "red"
//        border.width: 1
//    }


    Rectangle {
        id: volumeBar2
        width: 15
        height: 250
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 220
        anchors.leftMargin: -300
        border.color: "red"
        border.width: 1
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
        source: "bilder/UsbRahmen.png"
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
                width: parent.width; height: 30
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

