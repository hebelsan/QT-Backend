import QtQuick 2.7

Item {
    id: musicState
    objectName: "musicState"

    signal musicProgressTimerStarted()

    property bool showVolume: false
    property bool isPlaying: false
    property string title: "Current Title"
    // title duration in seconds
    property int titleDuration: 142
    property int currentTime: 0

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
        return getMinutes(currentTime);
    }

    function getSecondsCurentTitle() {
        return getSeconds(currentTime);
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

    function setCurrentTime(time) {
        currentTime = time
    }

    function setTitleDuration(time) {
        duration = time;
    }

    function setTitle(newTitle) {
        title = newTitle;
    }

    function movePlayTime() {
        musicState.musicProgressTimerStarted()
        if (currentTime <= titleDuration) {
            setCurrentTime(++currentTime)
        }
    }
}
