#include "Controller.hpp"
#include <iostream>

Controller::Controller() {
	systemState.mainView = START_VIEW;
	systemState.leftView = MEDIA;
	systemState.audioState.isPlaying = false;
	systemState.audioState.isPaused = false;
	systemState.audioState.currentTitle = "";
	systemState.audioState.volume = 1.0;
	player.open("file:///home/pi/test.mp3");
}

Controller* Controller::getInstance() {
 static Controller theInstance;
 return &theInstance;
}

// returns current mainView
MainViewEnum Controller::getMainView() {
	return systemState.mainView;
}

// return current leftView
LeftViewEnum Controller::getLeftView() {
	return systemState.leftView;
}

double Controller::getPlayerVolume() {
	return systemState.audioState.volume;
}

// set MainView
void Controller::setMainView(MainViewEnum m) {
	systemState.mainView = m;
}

// set LeftView
void Controller::setLeftView(LeftViewEnum l) {
	systemState.leftView = l;
}

// set the controller state
void Controller::setSystemstate(state newState) {
	systemState = newState;
}

// depending on current view the signal if forwarded
void Controller::sendEvent(EventEnum e) {
	switch (systemState.mainView)
	{
	case START_VIEW:
		startView.sendEvent(e, &systemState, &player);
   		break;
	case USB_VIEW:
		usbView.sendEvent(e, &systemState, &player);
		break;
	}
}
