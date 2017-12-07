import QtQuick 2.7

Item {
    height: 462
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    HFUTachometer{
        id: hfuTachometer
        visible: true
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 1
    }


}



