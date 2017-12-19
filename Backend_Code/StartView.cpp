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
			return CarCamView::getInstance();
			break;
		case BUTTON_DOWN:
			// leftView - 1
// 			if (static_cast<int>(systemState->leftView) == 0) {
// 				systemState->leftView = PHONE;
// 			} else {
// 				systemState->leftView = static_cast<LeftViewEnum>(static_cast<int>(systemState->leftView) - 1);
// 			}
			return PhoneView::getInstance();
			// std::cout << "? 5 " << control_daten->down << std::endl;
			break;
		case BUTTON_LEFT:
			return this;
			break;
		case BUTTON_RIGHT:
			return this;
			break;
		case RSB_TOP:
			globals.setOldState(this);
			return UsbView::getInstance();
			break;
		case BUTTON_A:
			// std::cout << "? 13 " << control_daten->a << std::endl;
			return this;
			break;
		case BUTTON_Y:
			globals.increaseVolume();
			return this;
			break;
		case WHEEL_TURN:
			return this;
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
		case WHEEL_DIRECTION:
			std::cout << "? 21 " << 1 << std::endl;
			// nextTitle
			break;
		case USB_PLUGGED_IN:
			std::cout << "? 30 1" << std::endl;
			globals.setOldState(this);
			return UsbView::getInstance();
		case USB_PLUGGED_OUT:
			return this;
			break;
	}
}
