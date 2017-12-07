import QtQuick 2.7
import hfu.enums.IndicatorLight 1.0
import hfu.enums.CruseControl 1.0

Item {
    id: canEventSink

    property int turnSignal: 2
    property real kphold
    property real kph
    property real rpmold: 1000
    property real rpm: 0
    property real fuel: 0.85
    property real range: 1000
    property real song_time: 100
    property string gear: "P"
    property real temperature: 0.1
    property Item activeLeftView: media
    property Item media: HFUMediaLeft{
        height: hfuDasboardLeftView.height
        width: hfuDasboardLeftView.width
    }
    property Item nav: HFUNavStyle{
        height: hfuDasboardLeftView.height
        width: hfuDasboardLeftView.width
    }
    property Item phone: HFUPhoneLeft{
        height: hfuDasboardLeftView.height
        width: hfuDasboardLeftView.width
    }
    property Item info: HFUInfoLeft{
        height: hfuDasboardLeftView.height
        width: hfuDasboardLeftView.width
        //children: warnings
    }
    property string warningSrc1:""
    property string warningSrc2:""
    property string warningSrc3:""
    property string warningSrc4:""
    property string warningSrc5:""
    property string warningSrc6:""
    property string warningSrc7:""
    property string warningSrc8:""
    property string warningSrc9:""

    property int zoomLevel:19

    property int distanceToTurn: 0

    //property int song_time:0

    function setRange(newRange){
        range = newRange
    }

    function increaseZoom(){
        console.log("increase");
        if (navItem.pos===0 && zoomLevel < 19)
            zoomLevel+=1;
    }

    function decreaseZoom(){
        console.log("decrease");
        if (navItem.pos===0 && zoomLevel > 1)
            zoomLevel-=1;
    }

    property int selectetContact: 0

    function selectNextContact(){
        if (phoneItem.pos===0 && selectetContact<7){
            selectetContact +=1
        }
    }
    function selectBeforeContact(){
        if (phoneItem.pos===0 && selectetContact>0){
            selectetContact -=1
        }
    }

    property color colorrpm: {
        var x;
        if (rpm<6000){
            return Qt.rgba(0.0,0.7,0.0,1);
        }
        else{
            if (rpm<7000){
                return Qt.rgba(0,0.55,1,1);
            }else{
                return "red"
            }
        }

    }

    //setting turn
    function setTurn(event){
        turnSignal = event;
    }
    //--------------------------------------------------------------------------------------------------------------------
    //setting rpm

    function setRpm(newRpm){
        rpmold = rpm
        rpm = newRpm;
    }

    Behavior on rpm{
        NumberAnimation {
            id: rpmanimation
            duration: 50
            easing.type: Easing.InOutQuad
            from: rpmold
        }
    }
    //--------------------------------------------------------------------------------------------------------------------
    //setting kph
    function setSpeed(newKph){
        kphold= kph
        kph = newKph;
    }

    Behavior on kph{
        NumberAnimation {
            id: kphanimation
            duration: 50
            easing.type: Easing.InOutQuad
            from: kphold
        }
    }

    //property Image warning1: warnings.warning1

    function setCarWarning(carWarnings){
        var i = 0
        var src =""

        // bitmask engine
        if ((carWarnings & IndicatorLight.Engine) === IndicatorLight.Engine){
            placeWarning("bilder/motorkontrollleuchte.jpg")
        }
        // bitmask coolant temp
        if ((carWarnings & IndicatorLight.CoolantTempHigh) === IndicatorLight.CoolantTempHigh){
            placeWarning("bilder/kuehlmittel_2.jpg")
        }
        // bitmask ESP
        if ((carWarnings & IndicatorLight.ESP) === IndicatorLight.ESP){
            placeWarning("bilder/esp.png")
        }
        // bitmask ABS
        if ((carWarnings & IndicatorLight.ABS) === IndicatorLight.ABS){
            placeWarning("bilder/abs.png")
        }
        // bitmask HandBrake
        if ((carWarnings & IndicatorLight.HandBrake) === IndicatorLight.HandBrake){
            placeWarning("bilder/handbremse.png")
        }

    }

    function placeWarning(src){
        var warning = [warningSrc1, warningSrc2, warningSrc3, warningSrc4, warningSrc5, warningSrc6, warningSrc7, warningSrc8, warningSrc9];
        var i = 0

        while(warning[i]!=="" && warning[i]!==src && i<9 ){
            i=i+1;
        }

        switch(i){
        case 0: warningSrc1=src;
            break;
        case 1: warningSrc2=src;
            break;
        case 2: warningSrc3=src;
            break;
        case 3: warningSrc4=src;
            break;
        case 4: warningSrc5=src;
            break;
        case 5: warningSrc6=src;
            break;
        case 6: warningSrc7=src;
            break;
        case 7: warningSrc8=src;
            break;
        case 8: warningSrc9=src;
            break;
        }

        //i=infoItem.pos
        while(infoItem.pos!==0){
            turnLeft()
        }
    }

    function setWarning(iD){
        var warning = [warningSrc1, warningSrc2, warningSrc3, warningSrc4, warningSrc5, warningSrc6, warningSrc7, warningSrc8, warningSrc9];
        var i = 0
        var src =""

        switch(iD){
        case 1: src= "bilder/airbagstoerung.jpg";
            break;
        case 2: src= "bilder/batterie.jpg";
            break;
        case 3: src="bilder/oeldruck.jpg";
            break;
        case 4: src="bilder/bremsbelagverschleiss.jpg";
            break;
        case 5: src="bilder/bremsfluessigkeit.jpg";
            break;
        case 6: src="bilder/kuehlmittel.jpg";
            break;
        case 7: src="bilder/motorkontrollleuchte.jpg";
            break;
        case 8: src="bilder/nebelscheinwerfer.jpg";
            break;
        default: src="";
            break;

        }

        while(warning[i]!=="" && warning[i]!==src && i<9 ){
            i=i+1;
        }

        switch(i){
        case 0: warningSrc1=src;
            break;
        case 1: warningSrc2=src;
            break;
        case 2: warningSrc3=src;
            break;
        case 3: warningSrc4=src;
            break;
        case 4: warningSrc5=src;
            break;
        case 5: warningSrc6=src;
            break;
        case 6: warningSrc7=src;
            break;
        case 7: warningSrc8=src;
            break;
        case 8: warningSrc9=src;
            break;
        }

        //i=infoItem.pos
        while(infoItem.pos!==0){
            turnLeft()
        }
    }

    //--------------------------------------------------------------------------------------------------------------------
    //setting Gear
    function setGear(newGear){
        gear = newGear;
    }
    //--------------------------------------------------------------------------------------------------------------------
    //setting Temp
    function setTemp(newTemp){
        temperature = newTemp;
    }
    //--------------------------------------------------------------------------------------------------------------------
    //setting Fuel
    function setFuel(newFuel){
        //console.log("fuel: ",newFuel)
        fuel = newFuel;
    }
    //set Left View
    function setMediaLeft(){
        activeLeftView = media;
    }
    function setNavleft(){
        activeLeftView = nav;
        nav.update();
    }
    function setPhoneleft(){
        activeLeftView = phone;
    }
    function setInfoLeft(){
        activeLeftView = info
    }

    function setLeftView(id){
        if (id===0){
            setMediaLeft()
        }
        else if (id===1){
            setPhoneleft()
        }
        else if (id===2){
            setInfoLeft()
        }
        else if (id===3){
            setNavleft()
        }
    }
    property color selectedRightColor: Qt.rgba(0,0.55,1,1)
    property color unSelectedRightColor: Qt.rgba(0,0.55,1,0.5)
    property int captionSizeSelectedRight: 24
    property int captionSizeUnselectedRight: 20


    property Text mediaItem: HFURightSelectionItem{
        id: mediaItem
        pos: 0
        caption: "Media"
        color: selectedRightColor
        font.pointSize: captionSizeSelectedRight
        font.underline:true

    }
    property Text navItem: HFURightSelectionItem{
        id: navItem
        pos: 1
        caption: "NAV"
        color: unSelectedRightColor
        font.pointSize: captionSizeUnselectedRight
        font.underline:false

    }
    property Text phoneItem: HFURightSelectionItem{
        id: phoneItem
        pos: 3
        caption: "Phone"
        color: unSelectedRightColor
        font.pointSize: captionSizeUnselectedRight
        font.underline:false
    }
    property Text infoItem: HFURightSelectionItem{
        id: infoItem
        pos: 2
        caption: "Info"
        color: unSelectedRightColor
        font.pointSize: captionSizeUnselectedRight
        font.underline:false
    }
    property Text activeTop: mediaItem
    property Text activeLeft: navItem
    property Text activeRight: phoneItem
    property Text activeBotom: infoItem

    function turnRight(){
        var itemList = [mediaItem, phoneItem, infoItem, navItem]
        for (var i=0;i<=itemList.length-1; i++){

            if(itemList[i].pos>0){
                itemList[i].pos=itemList[i].pos-1
                //item.width=item.parent.width/2
                if (itemList[i].pos===0){
                    setLeftView(i)
                }
            }else{
                itemList[i].pos=3
            }
            setProbs(itemList[i])
        }
    }
    function turnLeft(){
        var itemList = [mediaItem, phoneItem, infoItem, navItem]
        for (var i=0;i<=itemList.length-1; i++){

            if(itemList[i].pos<3){
                itemList[i].pos=itemList[i].pos+1
                //item.width=item.parent.width/2
            }else{
                itemList[i].pos=0
                setLeftView(i)
            }

            setProbs(itemList[i])
            //canEventSink.setPhoneleft()
        }
    }

    function setProbs(item){
        if(item.pos===0){
            item.color= selectedRightColor
            item.font.pointSize = captionSizeSelectedRight
            item.font.underline = true
            activeTop = item
            //activeTop = item
        }
        else if(item.pos===1){
            item.color= unSelectedRightColor
            item.font.pointSize = captionSizeUnselectedRight
            item.font.underline = false
            activeLeft = item
        }
        else if(item.pos===2){
            item.color= unSelectedRightColor
            item.font.pointSize = captionSizeUnselectedRight
            item.font.underline = false
            activeBotom = item
        }
        else if(item.pos===3){
            item.color= unSelectedRightColor
            item.font.pointSize = captionSizeUnselectedRight
            item.font.underline = false
            activeRight = item
        }
    }


    SequentialAnimation {
            running: true
            loops: 1

            // We want a small pause at the beginning, but we only want it to happen once.
            PauseAnimation {
                duration: 2000
            }

            ParallelAnimation{
                NumberAnimation {
                    target: canEventSink
                    property: "kph"
                    easing.type: Easing.InOutSine
                    from: 0
                    to: 280
                    duration: 1000
                }
                NumberAnimation {
                    target: canEventSink
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    from: 0
                    to: 9000
                    duration: 1000
                }
            }

            ParallelAnimation{
                NumberAnimation {
                    target: canEventSink
                    property: "kph"
                    easing.type: Easing.InOutSine
                    from: 280
                    to: 0
                    duration: 1000
                }
                NumberAnimation {
                    target: canEventSink
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    from: 9000
                    to: 0
                    duration: 1000
                }

                NumberAnimation {
                    target: canEventSink
                    property: "turnSignal"
                    duration: 1
                    to: 0
                    easing.type: Easing.InOutQuad
                }
            }


}
}
