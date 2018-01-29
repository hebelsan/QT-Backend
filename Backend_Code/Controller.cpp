#include "Controller.hpp"
#include <iostream>

Controller::Controller() {
	
	currentState = StartView::getInstance();
	globals = new GlobalParams();
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
	currentState = currentState->sendEvent(e, *globals);
}

void Controller::setMountpoint(std::string point)
{
	// sobald der USB-Stick unmounted wird, wird der Player gelöscht und alle Globalen Attribute.
	// somit wird der Absturz verhindert.
	if(point == "" && globals->getCurrentDirectory() != "")
	{
		delete globals;
		globals = new GlobalParams();
	}
	else globals->setMountpoint(point);
}
