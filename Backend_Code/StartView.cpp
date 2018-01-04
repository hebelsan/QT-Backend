#include "StartView.hpp"
#include "State.hpp"
#include <iostream>

using namespace std;

StartView* StartView::getInstance()
{
	static StartView theInstance;
	return &theInstance;
}

std::string StartView::getName()
{
	return string("Start View");
}

State* StartView::sendEvent(EventEnum event, GlobalParams &globals){
	// switch jedes Event
	switch (event) {
		case BUTTON_UP:
			// leftView + 1
			cout << "? 4 1" << endl;
			cout << "? 100 " <<  CarCamView::getInstance()->getId() << endl;
			return CarCamView::getInstance();
			break;
		case BUTTON_DOWN:
			cout << "? 5 1" << endl;
			cout << "? 100 " << PhoneView::getInstance()->getId() << endl;;
			return PhoneView::getInstance();
			// std::cout << "? 5 " << control_daten->down << std::endl;
			break;
		case RSB_TOP:
			globals.setOldState(this);
			cout << "? 11 1" << endl;
			return UsbView::getInstance();
			break;
		case BUTTON_A:
			globals.decreaseVolume();
			return this;
			break;
		case BUTTON_Y:
			globals.increaseVolume();
			return this;
			break;
		case WHEEL_TURN_R:
			return this;
			break;
		case WHEEL_TURN_L:
			break;
		case WHEEL_PRESSED:
			//if (systemState.leftView == MEDIA) {
				// std::cout << "? 22 " << control_daten->wheel_pressed << std::endl;
				// if (!systemState.audioState.isPlaying && control_daten->wheel_pressed == 1) {
			// globals.startPlaying();
					//systemState->audioState.isPlaying = true;
				//} else if (control_daten->wheel_pressed == 1) {
				//	player.pause();
				//	systemState.audioState.isPlaying = false;
				//}
			//}
			return this;
			break;
		case WHEEL_DIR_R:
			std::cout << "? 21 " << 1 << std::endl;
			// nextTitle
			break;
		case WHEEL_DIR_L:
			break;
		case USB_PLUGGED_IN:
			globals.setOldState(this);
			//std::cout << "? 30 1" << std::endl;
			cout << "? 100 " << UsbView::getInstance()->getId() << endl;
			return UsbView::getInstance();
		case USB_PLUGGED_OUT:
			return this;
			break;
	}
	return this;
}

int StartView::getId()
{
	return 1;
}
