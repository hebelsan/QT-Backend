#include "Controller.hpp"
#include <iostream>

Controller::Controller() {
	
	currentState = StartView::getInstance();
}

Controller* Controller::getInstance() {
	static Controller theInstance;
	return &theInstance;
}

State* Controller::getCurrentState()
{
	return currentState;
}

// depending on current view the signal if forwarded
void Controller::sendEvent(EventEnum e) {
	currentState = currentState->sendEvent(e, globals);
}

void Controller::setMountPoint(std::string point)
{
	globals.setMountpoint(point);
}