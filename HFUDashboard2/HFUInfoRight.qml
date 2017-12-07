import QtQuick 2.7
import QtQuick.Controls.Styles 1.4
//import QtLocation 5.5

/**
  * Implements the right side Info with: 1.)    date
  *                                      2.)    location
  *                                      3.)    time
  *                                      4.)    warnings
  *
  * Definitions of the warnings can be read below with the source of the images
  *
  */
Item{
    id: hfuInfoLeft
    visible: !showMenu.running

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
        x: 0
        y: 0
        z: 1
        source: "bilder/Info2.png"
    }

    Text{
        id: date
        x: 105
        y:20
        z:2

        text: canEventSink.date
        color: "#fdfdfd"
        font.bold: true
        font.pointSize: 15
    }

    Text{
        id: location
        x: 190
        y:123
        z:2

        text: "Furtwangen"
        color: "#fdfdfd"
        font.bold: true
        font.pointSize: 15
    }

    Text{
        id: time
        x: 218
        y:229
        z:2

        text: canEventSink.time
        color: "#fdfdfd"
        font.bold: true
        font.pointSize: 15
    }

    NumberAnimation on opacity {
        id: createAnimation
        from: 0
        to:1
        duration: 500
    }
    Component.onCompleted: createAnimation.start()
    onParentChanged: createAnimation.start()

    //Warnings on the right side info
    property string src1: "bilder/Partikelfilter.png"
    property string src2: "bilder/Reifendruck.png";
    property string src3: "bilder/Wischwasser.png";
    property string src4: "bilder/Ölstand.png";
    property string src5: "bilder/Batterie.png";
    property string src6: "bilder/ESC.png";
    property string src7: "bilder/Airbag.png";
    property string src8: "bilder/abs.png";

    Grid {
        id: warningsGrid
        scale: 0.8

        columns: 4
        columnSpacing: 3
        spacing: 3

        property color rectangleColor: "#161616"
        x: 83
        y: 292
        width: 20
        height: 20



        Image{
            id: warning1
            visible: canEventSink.warningSrcAll
            source: src1
        }
        Image{
            id: warning2
            visible: canEventSink.warningSrcAll
            source: src2
        }
        Image{
            id: warning3
            visible: canEventSink.warningSrcAll
            source: src3
        }
        Image{
            id: warning4
            visible: canEventSink.warningSrcAll
            source: src4
        }
        Image{
            id: warning5
            visible: canEventSink.warningSrcAll
            source: src5
        }
        Image{
            id: warning6
            visible: canEventSink.warningSrcAll
            source: src6
        }
        Image{
            id: warning7
            visible: canEventSink.warningSrcAll
            source: src7
        }
        Image{
            id: warning8
            visible: canEventSink.warningSrcAll
            source: src8
        }
    }

}
