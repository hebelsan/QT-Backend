import QtQuick 2.7
import QtQuick.Extras 1.4 //CircularGauge
//import QtGraphicalEffects 1.0
import QtQuick 2.2
// Workaround for QTBUG-37751; we need this import for RangeModel, although we shouldn't.
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Private 1.0
import QtQuick.Extras.Private 1.0


/**
  * Implements all functionality for the Tachometer
  *
  * Functionality is: 1.)   rpm
  *                   2.)   fuel
  *                   3.)   temperatur
  *                   4.)   needle
  *                   5.)   Images for the Tachometer
  *                   6.)   rpm count
  *                   7.)   fuel count
  *                   8.)   temperature count
  *                   9.)   kmh count
  *                   10.)  gear
  *                   11.)  Turn Signal left
  *                   12.)  Turn Signal right
  *                   13.)  warnings
  *
  */
Image {

    Canvas{
            id: canvas_drehzahl
            antialiasing: true

            property double centerHeight: canEventSink.rpm/13.4
            property int y_coord: 456-centerHeight

            property real minimumValue: 0
            property real maximumValue: 6000
            property real currentValue: canEventSink.rpm
            z: -1
            anchors.fill: parent
            anchors.topMargin: 0
            anchors.bottomMargin: -2
            anchors.leftMargin: -160

            onCurrentValueChanged: requestPaint()

            onPaint: {
                var ctx = getContext("2d");

                ctx.save();

                ctx.clearRect(0, 0, canvas_drehzahl.width, canvas_drehzahl.height)

                ctx.lineWidth = 300;
                ctx.fillStyle = "red"
                ctx.beginPath()
                ctx.fillRect(canvas_drehzahl.x, canvas_drehzahl.y_coord, 500, canvas_drehzahl.centerHeight)
                //ctx.moveTo(canvas.x, 400)
                //ctx.lineTo(canvas.x, 500)
                ctx.closePath()
                ctx.stroke()

                ctx.restore();
            }
        }

    Canvas{
            id: canvas_tank
            antialiasing: true

            property double centerHeight: canEventSink.fuel*1.38
            property int y_coord: 189-centerHeight

            property real minimumValue: 0
            property real maximumValue: 6000
            property real currentValue: canEventSink.fuel
            z: -1
            anchors.fill: parent
            anchors.topMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 150
            anchors.rightMargin: -160

            onCurrentValueChanged: requestPaint()

            onPaint: {
                var ctx = getContext("2d");

                ctx.save();

                ctx.clearRect(0, 0, canvas_tank.width, canvas_tank.height)

                ctx.lineWidth = 300;
                ctx.fillStyle = "red"
                ctx.beginPath()
                ctx.fillRect(canvas_tank.x, canvas_tank.y_coord, 500, canvas_tank.centerHeight)
                //ctx.moveTo(canvas.x, 400)
                //ctx.lineTo(canvas.x, 500)
                ctx.closePath()
                ctx.stroke()

                ctx.restore();
            }
        }

    Canvas{
            id: canvas_temp
            antialiasing: true

            property double centerHeight: canEventSink.temperature*1.80
            property int y_coord: 276

            property real minimumValue: 0
            property real maximumValue: 6000
            property real currentValue: canEventSink.temperature
            z: -1
            anchors.fill: parent
            anchors.topMargin: 0
            anchors.bottomMargin: -2
            anchors.leftMargin: 150
            anchors.rightMargin: -160

            onCurrentValueChanged: requestPaint()

            onPaint: {
                var ctx = getContext("2d");

                ctx.save();

                ctx.clearRect(0, 0, canvas_temp.width, canvas_temp.height)

                ctx.lineWidth = 300;
                ctx.fillStyle = "red"
                ctx.beginPath()
                ctx.fillRect(canvas_temp.x, canvas_temp.y_coord, 500, canvas_temp.centerHeight)
                //ctx.moveTo(canvas.x, 400)
                //ctx.lineTo(canvas.x, 500)
                ctx.closePath()
                ctx.stroke()

                ctx.restore();
            }
        }

    Image {
        id: needle
        x: 59
        y: 225
        visible: true
        source: "bilder/Zeiger_Komplett_1.png"
        transform: Rotation{origin.x: 169; origin.y: 3; angle: canEventSink.angle
        Behavior on angle{
            SpringAnimation{
                spring: 2
                damping: 0.5
            }
        }

        }
        smooth: true
    }

    Image{
        id: deckel
        x: 122
        y: 95
        width: 265
        height: 265
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        visible: true
        source: "bilder/Deckel_1.2.png"
    }

    Image{
        z: -1
        anchors.horizontalCenterOffset: -215
        x: 1
        y: -4
        width: 362
        height: 473
        anchors.horizontalCenter: parent.horizontalCenter
        id: drehzahl_deckel
        source: "bilder/Drehzahl_Deckel_1.2.png"
    }

    Image{
        z: -2
        anchors.horizontalCenterOffset: -220
        x: 0
        y: 0
        width: 316
        height: 466
        anchors.horizontalCenter: parent.horizontalCenter
        id: drehzahl
        source: "bilder/Drehzahl_1.2.png"
    }

    Image{
        id: tt_deckel
        x: 265
        y: -4
        width: 360
        height: 473
        z: -1
        source: "bilder/TT_Deckel_1.2.png"
    }

    Image{
        id: tt
        x: 292
        y: 0
        width: 306
        height: 465
        z: -2
        source: "bilder/TT_1.2.png"
    }

    Image{
        id:rpmcounter
        x: -127
        y: 204
        width: 132
        height: 58
        z: 1
        source:"bilder/RPM_Counter_1.png"
    }

    Text{
        id: rpmcount
        x: -77
        y: 225
        z: 1
        width: 10
        height: 80
        property int rpmcount: (canEventSink.rpm / 10)
        property int rpm: rpmcount.rpmcount * 10
        color: "#fdfdfd"

        text: rpmcount.rpm
        font.bold: true
        font.pointSize: 14

    }

    Image{
        id:ttcounter
        x: 476
        y: 200
        z: 1
        source:"bilder/Tank_Temp_Counter_1.png"
    }

    Text{
        id: tankcount
        x: 530
        y: 203
        z: 1
        width: 10
        height: 80
        property int tankcount: canEventSink.fuel
        color: "#fdfdfd"

        text: tankcount.tankcount
    }

    Text{
        id: tempcount
        x: 525
        y: 240
        z: 1
        width: 10
        height: 80
        property int tempcount: canEventSink.temperature
        color: "#fdfdfd"

        text: tempcount.tempcount
    }

    Text{
        id: kphcount
        x: 240
        y: 250
        width: 10
        height: 97
        property int speed: canEventSink.kph
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#fdfdfd"

        text: kphcount.speed
        anchors.verticalCenterOffset: 4
        anchors.horizontalCenterOffset: -32
        font.bold: true
        font.pointSize: 30
    }

    Text{
        id:kphstatic
        width:10
        height: 75
        property string kphshow: "kmh"
        x: 353
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#fdfdfd"

        text: kphstatic.kphshow
        font.italic: true
        font.pointSize: 17
        font.bold: true
        anchors.horizontalCenterOffset: 60
        anchors.verticalCenterOffset: 7
    }

    Text{
        id: gear
        width: 20
        height: 75
        property string gearshow: canEventSink.gear
        x: canEventSink.gear_x_pos
        y: 375
        color: canEventSink.gearTextColor

        text: gear.gearshow
        font.pointSize:27
        font.bold: true
        anchors.horizontalCenterOffset: 60
        anchors.verticalCenterOffset: 7
    }

    Item {
        id: blinker
        width: parent.width
        height: parent.height

        Connections {
            target: connector
            onTurnSignalLeftFrameReceived: {
                if(!blinkRight.running) {
                    if (blinkLeft.running) {
                        blinkLeft.stop();
                    } else {
                        blinkLeft.start();
                    }
                }
            }
            onTurnSignalRightFrameReceived: {
                if (!blinkLeft.running) {
                    if (blinkRight.running) {
                        blinkRight.stop();
                    } else {
                        blinkRight.start();
                    }
                }
            }
        }


        Image{
            id: leftturnsignal
            x: -82
            y: -4
            property bool clicked: false;
            visible: blinkLeft.running
            source: "bilder/Blinker_links.png"

            SequentialAnimation {
                    id: blinkLeft
                    running: false
                    loops: 5
                    NumberAnimation { target: leftturnsignal; property: "opacity"; to: 0; duration: 500}
                    NumberAnimation { target: leftturnsignal; property: "opacity"; to: 1.0; duration: 500}
            }
        }

        Image{
            id: rightturnsignal
            x: 481
            y: -4
            visible: blinkRight.running
            source: "bilder/Blinker_rechts.png"
        }

        SequentialAnimation {
                id: blinkRight
                running: false
                loops: 5
                NumberAnimation { target: rightturnsignal; property: "opacity"; to: 0; duration: 500}
                NumberAnimation { target: rightturnsignal; property: "opacity"; to: 1.0; duration: 500}
        }
    }

    Item{
            Image{
                x: 202
                y: 316
                width: 52
                height: 40
                source: "bilder/Bremsanlage.png"
                visible: canEventSink.warningSrcAll
            }

            Image{
                x: 149
                y: 235
                width: 52
                height: 40
                source: "bilder/Fahrlicht.png"
                visible: canEventSink.warningSrcAll
            }

            Image{
                x: 254
                y: 235
                width: 52
                height: 40
                source: "bilder/Nebelschlussleuchte.png"
                visible: canEventSink.warningSrcAll
            }

            Image{
                x: 306
                y: 235
                width: 52
                height: 40
                source: "bilder/Nebelscheinwerfer.png"
                visible: canEventSink.warningSrcAll
            }

            Image{
                x: 190
                y: 275
                width: 52
                height: 40
                source: "bilder/Motor.png"
                visible: canEventSink.warningSrcAll
            }

            Image{
                x: 238
                y: 275
                width: 52
                height: 40
                source: "bilder/Tueren.png"
                visible: canEventSink.warningSrcAll
            }

            Image{
                x: 136
                y: 275
                width: 52
                height: 40
                source: "bilder/Vorgluehen.png"
                visible: canEventSink.warningSrcAll
            }

            Image{
                x: 279
                y: 275
                width: 52
                height: 40
                source: "bilder/Tempomat.png"
                visible: canEventSink.warningSrcAll
            }

            Image{
                x: 202
                y: 235
                width: 52
                height: 40
                source: "bilder/Standlicht.png"
                visible: canEventSink.warningSrcAll
            }

            Image{
                x: 103
                y: 235
                width: 52
                height: 40
                source: "bilder/Fernlicht.png"
                visible: canEventSink.warningSrcAll
            }
        }


    id: image1
    property alias needle: needle
    width: 461
    x: -230
    y: 38.54
    source: "bilder/Tacho_1.2.png"
    fillMode: Image.PreserveAspectFit
    property int animationTime: 500
    property int moveAmount: 200

    Timer {
        id: minimizeTachoTimer
        interval: animationTime; running: false; repeat: false
        onTriggered: {
            usbView.visible = true;
        }
    }

    Timer {
        id: enlargeTachoTimer
        interval: animationTime; running: false; repeat: false
        onTriggered: {
            hfuDasboardRightView.visible = true;
            hfuDasboardLeftView.visible = true;
        }
    }

    Behavior on scale { PropertyAnimation {duration: animationTime} }
    Behavior on x { PropertyAnimation {duration: animationTime} }

    Connections {
        target: connector
        onSwitchUsbMediaMode: {
            if (!enlargeTachoTimer.running && !minimizeTachoTimer.running) {
                if (!usbView.visible) {
                    hfuDasboardRightView.visible = false;
                    hfuDasboardLeftView.visible = false;
                    image1.x = moveAmount;
                    image1.scale = 0.65;
                    minimizeTachoTimer.start();
                } else {
                    usbView.visible = false;
                    image1.scale = 1.0;
                    image1.x = -moveAmount;
                    enlargeTachoTimer.start();
                }
            }
        }
    }

}
