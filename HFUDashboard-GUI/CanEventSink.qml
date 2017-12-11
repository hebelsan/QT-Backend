import QtQuick 2.7
import hfu.enums.IndicatorLight 1.0
import hfu.enums.CruseControl 1.0
import hfu.enums.Gear 1.0

Item {
    id: canEventSink
    objectName: "canEventSink"

    property bool isPlaying: false
    property double angle: 292
    property int turnSignal: 2
    property bool leftTurnSignal: false
    property bool rightTurnSignal: false
    property bool warningSrcAll: false
    property real kphold
    property real kph
    property real rpmold: 1000
    property real rpm: 0
    property real fuel: 130
    property real range: 1000
    property string date: "01.01.2000"
    property string time: "00:00:00"
    property real song_time: 50
    property string gear: "P"
    property real gear_x_pos: 216
    property real temperature: 70
    property Item activeLeftView: media
    property Item media: HFUMediaLeft{
        height: hfuDasboardLeftView.height
        width: hfuDasboardLeftView.width
        // x: 107
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
    property string gearTextColor: "#fdfdfd";

    property int zoomLevel:19

    property int distanceToTurn: 0

    property int selectetContact:0

    property bool showVolume: false

    signal speedSignal(int speed)

    function setLeftViewToMedia() {
        setMediaLeft();
        mediaItem.pos = 0;
        navItem.pos = 1;
        infoItem.pos = 2;
        phoneItem.pos = 3;
        setProbs(mediaItem);
    }

    function setShowVolume(state) {
        showVolume = state;
    }

    function selectNextContact(){
        if (activeLeftView === phone && phoneItem.pos===0&& selectetContact<6)
            selectetContact+=1
    }
    function selectBeforeContact(){
        if (activeLeftView === phone && phoneItem.pos===0 && selectetContact>0)
            selectetContact-=1
    }

    function setRange(newRange){
        range = newRange
    }

    function increaseZoom(){
        if (activeLeftView === nav && navItem.pos===0 &&zoomLevel < 19)
            zoomLevel+=1;
    }

    function decreaseZoom(){
        if (activeLeftView === nav && navItem.pos===0&& zoomLevel > 1)
            zoomLevel-=1;
    }

    function setGearColorRed(){
        gearTextColor = "red"
    }

    function setGearColorDefault(){
        gearTextColor = "#fdfdfd"
    }

    function setGearXPosition(letters){
        if(letters === 1)
            gear_x_pos = 216;
        if(letters === 2)
            gear_x_pos = 200;
    }


    property color colorrpm: {
        var x;
        if (rpm<3000){
            return Qt.rgba(0.0,0.7,0.0,1);
        }
        else{
            if (rpm<5000){
                return Qt.rgba(0,0.55,1,1);
            }else{
                return "red"
            }
        }

    }

    property color colorshadow: {
        if (rpm<3000){
            return "#0000ff";
        }
        else{
            if (rpm<5000){
                return "#ff0000";
            }else{
                return "#00ffff"
            }
        }
    }

    //setting angle
    function setAngle(newAngle){
        angle = newAngle;
    }

    //setting turn
    function setTurn(event){
        turnSignal = event;
    }

    function setLeftTurnSignal(state){
        leftTurnSignal = state
    }
    function setRightTurnSignal(state){
        rightTurnSignal = state
    }

    //--------------------------------------------------------------------------------------------------------------------
    //setting rpm

    function setRpm(newRpm){
        if (newRpm >= 0 && newRpm <= 6000){
            rpmold = rpm
            rpm = newRpm;
        }
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
        canEventSink.speedSignal(newKph);
        kphold= kph
        kph = newKph;
		if(newKph <= 100){
			setAngle(1.5*newKph+292);
		}
		else{
			setAngle(0.75*newKph+366.5);
		}
    }

    Behavior on kph{
        NumberAnimation {
            id: kphanimation
            duration: 50
            easing.type: Easing.InOutQuad
            from: kphold
        }
    }

    //------------------------------------------------------------------------------------------------------------------------
    //setting date and time
    function setTime(newTime){
        time = newTime;
    }

    function setDate(newDate){
        date = newDate;
    }

    //-----------------------------------------------------------------------------------------------------------------------
    //setting the car warning
    //for setting the warnings seperately the warnings need their own visibility attribute being accessed the same way like setAllWarnings

    function setAllWarnings(){
        warningSrcAll = !warningSrcAll;
    }


    //--------------------------------------------------------------------------------------------------------------------
    //setting Gear
    function setGear(newGear){
        if (newGear === Gear.P){
            gear = "P";
            setGearColorDefault();
            setGearXPosition(1);
        }
        else if (newGear === Gear.R){
            gear = "R";
            setGearColorDefault();
            setGearXPosition(1);
        }
        else if (newGear === Gear.N){
            gear = "N";
            setGearColorDefault();
            setGearXPosition(1);
        }
        else if (newGear === Gear.D){
            gear = "D";
            setGearColorDefault();
            setGearXPosition(1);
        }
        else if (newGear === Gear.S){
            gear = "S";
            setGearColorDefault();
            setGearXPosition(1);
        }
        else if (newGear === Gear.M){
            gear = "M";
            setGearColorDefault();
            setGearXPosition(1);
        }
        else if (newGear === Gear.M_R){
            gear = "M";
            setGearColorRed();
            setGearXPosition(1);
        }
        else if (newGear === Gear.E){
            gear = "E";
            setGearColorDefault();
            setGearXPosition(1);
        }
        else if (newGear === Gear.MS){
            gear = "MS";
            setGearColorDefault();
            setGearXPosition(2);
        }
        else if (newGear === Gear.S_R){
            gear = "S";
            setGearColorRed();
            setGearXPosition(1);
        }
        else if (newGear === Gear.MS_R){
            gear = "MS";
            setGearColorRed();
            setGearXPosition(2);
        }
    }
    //--------------------------------------------------------------------------------------------------------------------
    //setting Temp
    function fillTemp(newTemp){
        temperature = newTemp;
    }

    function reduceTemp(newTemp){
        temperature = newTemp;
    }

    //--------------------------------------------------------------------------------------------------------------------
    //setting Fuel
    function fillFuel(newFuel){
        fuel = newFuel;
    }

    function reduceFuel(newFuel){
        if(fuel !=0)
        fuel = newFuel;
    }

    function startAnimation(targets){
        //targets={nav, phone, info}
        destroyAnimation.targets = targets;
        destroyAnimation.start()
    }

    NumberAnimation on opacity{
        id: destroyAnimation
        from: 1
        to:0
        duration: 500
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
            startAnimation([phone, nav, info]);
        }
        else if (id===1){
            setPhoneleft()
            startAnimation([media, nav, info]);
        }
        else if (id===2){
            setInfoLeft()
            startAnimation([phone, nav, media]);
        }
        else if (id===3){
            setNavleft()
            startAnimation([phone, media, info]);
        }
    }
        property color selectedRightColor: "#ad2020"
        property color unSelectedRightColor: "#130303"
        property int captionSizeSelectedRight: 30
        property int captionSizeUnselectedRight: 20


    property Text mediaItem: HFURightSelectionItem{
        id: mediaItem
        pos: 0
        caption: "Media"
        color: selectedRightColor
        font.pointSize: captionSizeSelectedRight
        font.underline: false

    }
    property Text navItem: HFURightSelectionItem{
        id: navItem
        pos: 1
        caption: "Nav"
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

    //------------------------------------------------------------------------------------------
    //functions for switching between media, phone, info, nav

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

    //--------------------------------------------------------------------------------------------------
    //if switching between media, phone, info, nav the selected item gets red and appear in the middle

    function setProbs(item){
        if(item.pos===0){
            item.color= selectedRightColor
            item.font.pointSize = captionSizeSelectedRight
            item.font.underline = false
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
}
