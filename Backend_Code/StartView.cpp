#include "StartView.hpp"
#include <iostream>

using namespace std;

void StartView::sendEvent(EventEnum event, struct state* systemState, GstPlayer* player) const {
	// switch jedes Event
	switch (event) {
		case BUTTON_UP:
			// leftView + 1
			if (static_cast<LeftViewEnum>(static_cast<int>(systemState->leftView) + 1) == endEnum) {
				systemState->leftView = MEDIA;
			} else {
				systemState->leftView = static_cast<LeftViewEnum>(static_cast<int>(systemState->leftView) + 1);
			}
			// std::cout << "? 4 " << control_daten->up << std::endl;
   			break;
		case BUTTON_DOWN:
			// leftView - 1
			if (static_cast<int>(systemState->leftView) == 0) {
				systemState->leftView = PHONE;
			} else {
				systemState->leftView = static_cast<LeftViewEnum>(static_cast<int>(systemState->leftView) - 1);
			}
			// std::cout << "? 5 " << control_daten->down << std::endl;
			break;
		case BUTTON_LEFT:
			// only works if leftview is phone
			if (systemState->leftView == PHONE) {
				// std::cout << "? 6 " << control_daten->right << std::endl;
			}
			break;
		case BUTTON_RIGHT:
			// only works if leftview is phone
			if (systemState->leftView == PHONE) {
				// std::cout << "? 7 " << control_daten->left << std::endl;
			}
			break;
		case RSB_TOP:
			systemState->mainView = USB_VIEW;
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
			break;
		case WHEEL_PRESSED:
			//if (systemState.leftView == MEDIA) {
				// std::cout << "? 22 " << control_daten->wheel_pressed << std::endl;
				// if (!systemState.audioState.isPlaying && control_daten->wheel_pressed == 1) {
					player->play();
					systemState->audioState.isPlaying = true;
				//} else if (control_daten->wheel_pressed == 1) {
				//	player.pause();
				//	systemState.audioState.isPlaying = false;
				//}
			//}
			break;
		case WHEEL_DIRECTION:
			// std::cout << "? 21 " << control_daten->wheel_direction << std::endl;
			// nextTitle
			break;
		case USB_PLUGGED_IN:
			std::cout << "? 11 " << std::endl;
			break;
		case USB_PLUGGED_OUT:
			break;
	}
}
