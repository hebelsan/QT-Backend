#include "Controller.hpp"
#include <iostream>

Controller::Controller() {
	systemState.mainView = START_VIEW;
	systemState.leftView = MEDIA;
	systemState.audioState.isPlaying = false;
	systemState.audioState.isPaused = false;
	systemState.audioState.currentTitle = "";
	systemState.audioState.volume = 1.0;
	player.open("file:///home/alex/Music/MarioLand.mp3");
}

Controller* Controller::getInstance() {
 static Controller theInstance;
 return &theInstance;
}

// returns current mainView
MainView Controller::getMainView() {
	return systemState.mainView;
}

// return current leftView
LeftView Controller::getLeftView() {
	return systemState.leftView;
}

double Controller::getPlayerVolume() {
	return systemState.audioState.volume;
}

// set MainView
void Controller::setMainView(MainView m) {
	systemState.mainView = m;
}

// set LeftView
void Controller::setLeftView(LeftView l) {
	systemState.leftView = l;
}

// checks if the View allows the Event
// If so: the event is send to the Gui
// IF not: no Signal is send
void Controller::sendEvent(Event e) {
	// switch jedes Event
	switch (e) {
		case BUTTON_UP:
			// leftView + 1
    			if (systemState.mainView == START_VIEW) {
				if (static_cast<LeftView>(static_cast<int>(systemState.leftView) + 1) == endEnum) {
					systemState.leftView = MEDIA;
				} else {
					systemState.leftView = static_cast<LeftView>(static_cast<int>(systemState.leftView) + 1);
				}
				// std::cout << "? 4 " << control_daten->up << std::endl;
			}
   			break;
		case BUTTON_DOWN:
			// leftView - 1
			if (systemState.mainView == START_VIEW) {
				if (static_cast<int>(systemState.leftView) == 0) {
					systemState.leftView = PHONE;
				} else {
					systemState.leftView = static_cast<LeftView>(static_cast<int>(systemState.leftView) - 1);
				}
				// std::cout << "? 5 " << control_daten->down << std::endl;
			}
			break;
		case BUTTON_LEFT:
			// only works if leftview is phone
			if (systemState.mainView == START_VIEW && systemState.leftView == PHONE) {
				// std::cout << "? 6 " << control_daten->right << std::endl;
			}
			break;
		case BUTTON_RIGHT:
			// only works if leftview is phone
			if (systemState.mainView == START_VIEW && systemState.leftView == PHONE) {
				// std::cout << "? 7 " << control_daten->left << std::endl;
			}
			break;
		case RSB_TOP:
			if (systemState.mainView == START_VIEW) {
				systemState.mainView = USB_VIEW;
			} else if (systemState.mainView == USB_VIEW) {
				systemState.mainView = START_VIEW;
			}
			// std::cout << "? 11 " << control_daten->rsb_top << std::endl;
			break;
		case BUTTON_A:
			// Volume Down
			if (systemState.audioState.volume != 0) {
				systemState.audioState.volume -= 0.05;
			}
			player.setVolume(systemState.audioState.volume);
			// std::cout << "? 13 " << control_daten->a << std::endl;
			break;
		case BUTTON_Y:
			// Volume UP
			if (systemState.audioState.volume != 1) {
				systemState.audioState.volume += 0.05;
			}
			player.setVolume(systemState.audioState.volume);
			// std::cout << "? 14 " << control_daten->b << std::endl;
			break;
		case WHEEL_TURN:
			if (systemState.mainView == USB_VIEW) {
				// std::cout << "? 20 " << static_cast<int16_t>(control_daten->wheel_turns) << std::endl;
				// currenTitle ++ / --
			}
			break;
		case WHEEL_PRESSED:
			if ( (systemState.mainView == START_VIEW && systemState.leftView == MEDIA) || systemState.mainView == USB_VIEW) {
				// std::cout << "? 22 " << control_daten->wheel_pressed << std::endl;
				// if (!systemState.audioState.isPlaying && control_daten->wheel_pressed == 1) {
					player.play();
					systemState.audioState.isPlaying = true;
				//} else if (control_daten->wheel_pressed == 1) {
				//	player.pause();
				//	systemState.audioState.isPlaying = false;
				//}
			}
			break;
		case WHEEL_DIRECTION:
			if (systemState.mainView == USB_VIEW) {
				// std::cout << "? 21 " << control_daten->wheel_direction << std::endl;
				// nextTitle
			}
			break;
		case USB_PLUGGED_IN:
			if (systemState.mainView != USB_VIEW) {
				std::cout << "? 11 " << std::endl;
			}
			break;
		case USB_PLUGGED_OUT:
			if (systemState.mainView == USB_VIEW) {
				std::cout << "? 11 " << std::endl;
			}
			break;
	}
}
