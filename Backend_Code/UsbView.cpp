#include "UsbView.hpp"
#include <iostream>

using namespace std;

UsbView::UsbView() : State()
{
	//medium = "";
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
		case RSB_TOP:
			return globals.getOldState();
			// std::cout << "? 11 " << control_daten->rsb_top << std::endl;
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
			break;
		case WHEEL_DIR_L:
			// TODO rückwärts spulen
			break;
		case USB_PLUGGED_IN:
			// Stay in this view;
			return this;
			break;
		case USB_PLUGGED_OUT:
			//std::cout << "? 11 1" << std::endl;
			std::cout << "? 100 " << globals.getOldState()->getId() << std::endl;
			return globals.getOldState();
			break;
	}
	return this;
}

int UsbView::getId()
{
	return 50;
}