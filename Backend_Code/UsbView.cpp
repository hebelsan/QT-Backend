#include "UsbView.hpp"
#include <iostream>

using namespace std;

UsbView::UsbView() : State()
{
	currentSelect = 0;
	medium = "";
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
	if(medium != globals.getMountpoint())
		currentSelect = 0;
	
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
			// std::cout << "? 13 " << control_daten->a << std::endl;
			break;
		case BUTTON_Y:
			// Volume UP
			globals.increaseVolume();
			// std::cout << "? 14 " << control_daten->b << std::endl;
			break;
		case WHEEL_TURN:
			// std::cout << "? 20 " << static_cast<int16_t>(control_daten->wheel_turns) << std::endl;
			// currenTitle ++ / --
			break;
		case WHEEL_PRESSED:
			// std::cout << "? 22 " << control_daten->wheel_pressed << std::endl;
			// if (!systemState.audioState.isPlaying && control_daten->wheel_pressed == 1) {
			
			//} else if (control_daten->wheel_pressed == 1) {
			//	player.pause();
			//	systemState.audioState.isPlaying = false;
			//}
			break;
		case WHEEL_DIRECTION:
			// std::cout << "? 21 " << control_daten->wheel_direction << std::endl;
			// nextTitle
			break;
		case USB_PLUGGED_IN:
			// Stay in this view;
			return this;
			break;
		case USB_PLUGGED_OUT:
			std::cout << "? 11 1" << std::endl;
			return globals.getOldState();
			break;
	}
	return this;
}
