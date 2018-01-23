#include "UsbView.hpp"
#include <iostream>

using namespace std;

UsbView::UsbView() : State()
{
	//medium = "";
	pout = PipeControl::getInstance();
}

State* UsbView::getInstance()
{
	static UsbView theInstance;
	return &theInstance;
}

std::string UsbView::getName()
{
	return std::string("USB View");
}

State* UsbView::sendEvent(EventEnum event, GlobalParams& globals) {
	// Falls sich Medium ändert, zurücksetzen.
	
	// switch jedes Event
	switch (event) {
		case BUTTON_UP:
   			break;
		case BUTTON_DOWN:
			break;
		case BUTTON_LEFT:
			break;
		case BUTTON_RIGHT:
			break;
		case BUTTON_A:
			//Volume DOWN
			globals.decreaseVolume();
			break;
		case BUTTON_Y:
			// Volume UP
			globals.increaseVolume();
			break;
		case WHEEL_TURN_R:
			globals.nextSelect();
			break;
		case WHEEL_TURN_L:
			globals.previousSelect();
			break;
		case WHEEL_PRESSED:
			globals.loadSelection();
			break;
		case WHEEL_DIR_R:
			// TODO spulen
			// std::cout << "? 21 " << control_daten->wheel_direction << std::endl;
			// nextTitle
			globals.seek(1);
			break;
		case WHEEL_DIR_L:
			// TODO rückwärts spulen
			globals.seek(-1);
			break;
		case USB_PLUGGED_IN:
			// Stay in this view;
			return this;
			break;
		case USB_PLUGGED_OUT:
			pout->add("? 100 " + to_string(globals.getOldState()->getId()));
			return globals.getOldState();
			break;
		case RSB_TOP:
			pout->add("? 100 " + to_string(globals.getOldState()->getId()));
			return globals.getOldState();
	}
	return this;
}

int UsbView::getId()
{
	return 50;
}