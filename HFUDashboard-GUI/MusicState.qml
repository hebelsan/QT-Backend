import QtQuick 2.7

Item {
    id: musicState
    objectName: "musicState"

    signal musicProgressTimerStarted()

    property bool showVolume: false
    property bool isPlaying: false
    property string titleCache: ""
    property string title: ""
    // title duration in seconds
    property int tilteDurationCache: 0
    property int titleDuration: 0
    property int currentPlayTimeSeconds: 0
    property string coverPath: "bilder/UsbView/NotenSchluessel.jpg"

    function setShowVolume(state) {
        showVolume = state;
    }

    // takes a time in seconds(int) and returns minutes
    function getMinutes(time) {
        return parseInt((time / 60), 10)
    }

    function getSeconds(time) {
        return (time % 60)
    }

    function getMinutesCurentTitle() {
        return getMinutes(currentPlayTimeSeconds);
    }

    function getSecondsCurentTitle() {
        return getSeconds(currentPlayTimeSeconds);
    }

    function getMinutesTitleFullDuration() {
        return getMinutes(titleDuration);
    }

    function getSecondsTitleFullDuration() {
        return getSeconds(titleDuration);
    }

    function getFormatedCurrentTime() {
        if (getSecondsCurentTitle() < 10) {
            return getMinutesCurentTitle() + ":0" + getSecondsCurentTitle();
        } else {
        return getMinutesCurentTitle() + ":" + getSecondsCurentTitle();
        }
    }

    function getFormatedTitleFullDuration() {
        if (getSecondsTitleFullDuration() < 10) {
            return getMinutesTitleFullDuration() + ":0" + getSecondsTitleFullDuration()
        } else {
            return getMinutesTitleFullDuration() + ":" + getSecondsTitleFullDuration()
        }
    }

    // sets the current playtime in seconds
    function setCurrentTime(time) {
        currentPlayTimeSeconds = time
    }

    function setTitleDuration(time) {
        duration = time;
    }

    function setTitle(newTitle) {
        title = newTitle;
    }

    function movePlayTime(seconds) {
        if (seconds > titleDuration)
            setCurrentTime(0);
        else
            setCurrentTime(seconds);
        musicState.musicProgressTimerStarted()
    }
}
