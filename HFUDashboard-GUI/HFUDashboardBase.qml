import QtQuick 2.7
import QtQuick.Controls 2.0
//import QtQuick.Layouts 1.0


ApplicationWindow {
    visible: true
    id: hfuDasboardBase
    title: qsTr("HFU Dashboard")
    width: 1440
    height: 540
    color: "#000000"

    property int gearTest: 1

    CanEventSink{
        id: canEventSink
    }

    MusicState{
        id: musicState
    }

    function getCANEventSink(){
        console.log("request can", canEventSink.turnSignal)
        return canEventSink
    }

    Timer {
        id: timer
    }

    function delay(delayTime) {
        timer.interval = delayTime;
        timer.repeat = false;
        timer.start();
    }

    Item {
        id: keyhandler
        focus:true
        Keys.onReleased: {         
            if(event.key===Qt.Key_Up){
                delay(2)
                if(canEventSink.kph+1 <= 320){
                    canEventSink.setSpeed(320)
                }
                else{
                    canEventSink.setSpeed(320)
                }
                if(canEventSink.rpm+100 <= 6000){
                    canEventSink.setRpm(canEventSink.rpm+100)
                }
                else{
                    canEventSink.setRpm(6000)
                }

                canEventSink.increaseZoom()
            }
            else if(event.key===Qt.Key_Down){
                delay(2)
                if(canEventSink.kph-1 >= 0){
                    canEventSink.setSpeed(canEventSink.kph-1)
                }
                else{
                    canEventSink.setSpeed(0)
                }
                if(canEventSink.rpm-20 >= 0){
                    canEventSink.setRpm(canEventSink.rpm-20)
                }
                else{
                    canEventSink.setRpm(0)
                }
                canEventSink.decreaseZoom()
            }
            else if(event.key===Qt.Key_Left){
                connector.turnSignalLeftFrameReceived();
            }
            else if(event.key===Qt.Key_Right){
                connector.turnSignalRightFrameReceived();
            }
            else if(event.key===Qt.Key_W){
                if(canEventSink.turnSignal==2){
                    canEventSink.setTurn(0)
                }else
                    canEventSink.setTurn(2)
            }
            else if(event.key===Qt.Key_U){
                if(gearTest < 11){
                    gearTest++;
                    canEventSink.setGear(gearTest);
                }
            }
            else if(event.key===Qt.Key_D){
                if(gearTest > 1){
                    gearTest--;
                    canEventSink.setGear(gearTest);
                }
            }
            else if(event.key===Qt.Key_O){
                if(canEventSink.temperature+1 <= 100){
                    canEventSink.fillTemp(canEventSink.temperature+1)
                }
                else{
                    canEventSink.fillTemp(100)
                }
            }
            else if(event.key===Qt.Key_L){
                if(canEventSink.temperature-1 >= 0){
                    canEventSink.reduceTemp(canEventSink.temperature-1)
                }
                else{
                    canEventSink.reduceTemp(0)
                }
            }
            else if(event.key===Qt.Key_I){
                if(canEventSink.fuel+1 <= 130){
                    canEventSink.fillFuel(canEventSink.fuel+1)
                }
                else{
                    canEventSink.fillFuel(130)
                }
            }
            else if(event.key===Qt.Key_K){
                if(canEventSink.fuel-1 >= 0){
                    canEventSink.reduceFuel(canEventSink.fuel-1)
                }
                else{
                    canEventSink.reduceFuel(0)
                }
            }
            else if(event.key===Qt.Key_R){
                canEventSink.turnRight();
                connector.menuStateFrameReceived();
            }
            else if(event.key===Qt.Key_F){
                canEventSink.turnLeft();
                connector.menuStateFrameReceived();
            }
            else if(event.key===Qt.Key_E){
                canEventSink.selectNextContact()
                            canEventSink.decreaseZoom()
            }
            else if(event.key===Qt.Key_Q){
                canEventSink.selectBeforeContact()
                            canEventSink.increaseZoom()
            }
            else if(event.key===Qt.Key_1){
                connector.setStartView();
            }
            else if(event.key===Qt.Key_2){
                connector.setCarCamView();
            }
            else if(event.key===Qt.Key_3){
                connector.setInfoView();
            }
            else if(event.key===Qt.Key_4){
                connector.setPhoneView();
            }
            else if(event.key===Qt.Key_5){
                connector.setUsbView();
            }
            else if(event.key===Qt.Key_6){
                canEventSink.setWarning(6);
            }
            else if(event.key===Qt.Key_7){
                canEventSink.setWarning(7);
            }
            else if(event.key===Qt.Key_8){
                canEventSink.setWarning(8);
            }
            else if(event.key===Qt.Key_9){
                canEventSink.setWarning(9);
            }
            else if(event.key===Qt.Key_P){
                canEventSink.setAllWarnings();
            }
            else if(event.key===Qt.Key_M){
                connector.menuStateFrameReceived();
            }
            else if(event.key===Qt.Key_Y){
                 connector.volumeUpFrameReceived();
            }
            else if(event.key===Qt.Key_X){
                 connector.volumeDownFrameReceived();
            }
            else if(event.key===Qt.Key_C){
                connector.musicPlayButtonPressed();
                connector.musicPauseButtonPressed();
            }
            else if(event.key===Qt.Key_V){
                 connector.audioWheelTurnedLeft();
            }
            else if(event.key===Qt.Key_B){
                 connector.audioWheelTurnedRight();
            }
            else if(event.key===Qt.Key_N){
                connector.switchUsbMediaMode();
            }
            else if(event.key===Qt.Key_A){
                // connector.musicBackwardButtonPressed();
            }
            else if(event.key===Qt.Key_S){
                // connector.musicForwardButtonPressed();
            }
            else if(event.key===Qt.Key_Z){
                // connector.musicWheelDirectionNormal();
            }
            else if(event.key===Qt.Key_Escape){
                close()
            }
        }
    }


    /**
      * Slots for receiving signals from the Connector class
      *
      */
    Item {
        Connections {
            target: connector
            onSetStartView: {
                if (usbView.visible == false) {
                    canEventSink.setLeftViewToMedia();
                } else {
                    connector.switchUsbMediaMode();
                    canEventSink.setLeftViewToMedia();
                }
            }
            onSetCarCamView: {
                if (usbView.visible == false) {
                    canEventSink.setLeftViewToNav();
                } else {
                    connector.switchUsbMediaMode();
                    canEventSink.setLeftViewToNav();
                }
            }
            onSetInfoView: {
                if (usbView.visible == false) {
                    canEventSink.setLeftViewToInfo()
                } else {
                    connector.switchUsbMediaMode();
                    canEventSink.setLeftViewToInfo()
                }
            }
            onSetPhoneView: {
                if (usbView.visible == false) {
                    canEventSink.setLeftViewToPhone()
                } else {
                    connector.switchUsbMediaMode();
                    canEventSink.setLeftViewToPhone()
                }
            }
            onSetUsbView: {
                if (usbView.visible == false)
                    connector.switchUsbMediaMode();
            }
            onSpeedFrameReceived: {
                canEventSink.setSpeed(speed);
            }
            onRpmFrameReceived: {
                canEventSink.setRpm(rpm);
            }
            onGearFrameReceived: {
                canEventSink.setGear(gear);
            }
            onRangeFrameReceived: {
                canEventSink.setRange(range);
            }
            onFuelFrameReceived: {
                canEventSink.fillFuel(fuel);
            }
            onTemperatureFrameReceived: {
                canEventSink.fillTemp(temperature);
            }
            onDateFrameReceived: {
                canEventSink.setDate(date);
            }
            onTimeFrameReceived: {
                canEventSink.setTime(time);
            }
            onDashboardMenuRightFrameReceived: {
                canEventSink.turnRight();
            }
            onDashboardMenuLeftFrameReceived: {
                canEventSink.turnLeft();
            }
            onWarningFrameReceived: {
                canEventSink.setAllWarnings();
            }
            onDashboardRollerUpFrameReceived:{
                canEventSink.increaseZoom();
                canEventSink.selectBeforeContact();
            }
            onDashboardRollerDownFrameReceived:{
                canEventSink.decreaseZoom();
                canEventSink.selectNextContact();
            }
            onMusicPlayButtonPressed: {
                musicState.title = musicState.titleCache;
                musicState.titleDuration = musicState.tilteDurationCache;
                musicState.coverPath = musicState.coverPathCache;
            }
            onCurrentTitleSeconds: {
                musicState.movePlayTime(seconds);
            }
            onMusicFastForward: {
                connector.musicForwardButtonPressed();
            }
            onMusicPlayTimeNormal: {
                connector.musicWheelDirectionNormal();
            }
            onMusicWindBack: {
                connector.musicBackwardButtonPressed();
            }
        }
    }

    Item{
        id: mainView
        visible: true
        width: 2880
        height: 1080
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        HFUDashboardLeftView{
            id: hfuDasboardLeftView
            // x: -107
            // y: 38
            width: 365
            z: 1
            height: 465
            anchors.right: hfuDasboardMiddleView.left
            anchors.rightMargin: 462
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 38
        }

        HFUDashboardMiddleView{
            id: hfuDasboardMiddleView
            width: 0
            height: parent.height
            anchors.topMargin: 1
        }


        HFUDashboardRightView{
            id: hfuDasboardRightView
            x: 1027
            y: 60
            width: 365
            z: 1
            height: 465
            anchors.right: hfuDasboardMiddleView.right
            anchors.rightMargin: -672
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
        }
    }

    Item{
        id: usbView
        visible: false
        width: 2880
        height: 1080
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        HFUDashboardUsbView{
            id: hfuDashboardUsbView
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.left: parent.left
            anchors.leftMargin: 500
            width: 800
            height: 800
        }


    }
}
