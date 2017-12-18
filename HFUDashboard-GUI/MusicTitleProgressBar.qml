import QtQuick 2.7

Item {
    id: progressBar

    Image {
        id: emptyProgressBar
        width: parent.width
        height: 20
        anchors.top: parent.top
        anchors.left: parent.left
        source: "bilder/UsbView/Bar.png"
    }
    Image {
        id: fullProgressBar
        width: 0
        height: 20
        anchors.top: parent.top
        anchors.left: parent.left
        source: "bilder/UsbView/Playbar.png"
    }
    Image {
        id: progressButton
        width: 18
        height: 18
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: -4
        source: "bilder/UsbView/Playposition.png"
    }
    Text {
        id: currentTime
        width: 10
        height: 10
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 15
        text: musicState.getFormatedCurrentTime()
        font.pointSize: 10
        color: "white"
    }
    Text {
        id: fullDuration
        width: 10
        height: 10
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 15
        anchors.rightMargin: 10
        text: musicState.getFormatedTitleFullDuration()
        font.pointSize: 10
        color: "white"
    }
}
