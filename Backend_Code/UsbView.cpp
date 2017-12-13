#include "UsbView.hpp"
#include <iostream>

using namespace std;

void UsbView::sendEvent(EventEnum event, struct state* systemState, GstPlayer* player) const {
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
			systemState->mainView = START_VIEW;
			// std::cout << "? 11 " << control_daten->rsb_top << std::endl;
			break;
		case BUTTON_A:
			// Volume Down
			if (systemState->audioState.volume > 0.0) {
				systemState->audioState.volume -= 0.05;
			}
			player->setVolume(systemState->audioState.volume);
			// std::cout << "? 13 " << control_daten->a << std::endl;
			break;
		case BUTTON_Y:
			// Volume UP
			if (systemState->audioState.volume < 1.0) {
				systemState->audioState.volume += 0.05;
			}
			player->setVolume(systemState->audioState.volume);
			// std::cout << "? 14 " << control_daten->b << std::endl;
			break;
		case WHEEL_TURN:
			// std::cout << "? 20 " << static_cast<int16_t>(control_daten->wheel_turns) << std::endl;
			// currenTitle ++ / --
			break;
		case WHEEL_PRESSED:
			// std::cout << "? 22 " << control_daten->wheel_pressed << std::endl;
			// if (!systemState.audioState.isPlaying && control_daten->wheel_pressed == 1) {
			player->play();
			systemState->audioState.isPlaying = true;
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
			// get title
			break;
		case USB_PLUGGED_OUT:
			std::cout << "? 11 " << std::endl;
			break;
	}
}
