import QtQuick 2.7



/**
  * Implements the Menue and gets 3 items
  *
  */
Item{
    id:hfuDashboardRightView

    HFUInfoRight {
        id: hfuInfoRight
    }

    Connections {
        target: connector
        onMenuStateFrameReceived: {
            if (showMenu.running)
                showMenu.restart();
            else
                showMenu.start();
        }
    }

    Timer {
        id: showMenu
        interval: 2000; running: false; repeat: false
    }


        Image{
         x: 151
         y: 104
         source: "bilder/Menuee_durch3.png"
         visible: showMenu.running

         Item{
           id: topSelect
           anchors.horizontalCenter: parent.horizontalCenter
           anchors.verticalCenter: parent.verticalCenter
           anchors.verticalCenterOffset: -canEventSink.activeTop.height/2
           anchors.horizontalCenterOffset: -canEventSink.activeTop.width+32
           children: canEventSink.activeTop
       }

       Item{
           id: leftSelect
           anchors.horizontalCenter: parent.horizontalCenter
           anchors.verticalCenter: parent.verticalCenter
           anchors.verticalCenterOffset: -parent.height/3.5
           anchors.horizontalCenterOffset: -canEventSink.activeLeft.width+32
           children: canEventSink.activeLeft

       }

       Item{
           id:rightSelect
           anchors.horizontalCenter: parent.horizontalCenter
           anchors.verticalCenter: parent.verticalCenter
           anchors.verticalCenterOffset: parent.height/5.5
           anchors.horizontalCenterOffset: -canEventSink.activeRight.width+32
           children: canEventSink.activeRight
       }


    }
}

