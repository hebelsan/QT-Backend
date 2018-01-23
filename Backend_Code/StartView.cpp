#include "StartView.hpp"
#include "State.hpp"

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
			//pout->add( "? 4 1" );
			pout->add( "? 100 " + to_string(CarCamView::getInstance()->getId() ));
			return CarCamView::getInstance();
			break;
		case BUTTON_DOWN:
			//pout->add("? 5 1" );
			pout->add( "? 100 " + to_string(PhoneView::getInstance()->getId() ));;
			return PhoneView::getInstance();
			// std::cout << "? 5 " << control_daten->down << std::endl;
			break;
		case RSB_TOP:
			globals.setOldState(this);
			pout->add( "? 100 " + to_string(UsbView::getInstance()->getId() ));
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
			globals.togglePlayer();
			return this;
			break;
		case WHEEL_DIR_R:
			globals.seek(1);
			break;
		case WHEEL_DIR_L:
			globals.seek(-1);
			break;
		case MM_BTN_R:
			globals.loadNextSong();
			break;
		case MM_BTN_L:
			globals.loadPreviousSong();
			break;
		case USB_PLUGGED_IN:
			globals.setOldState(this);
			//std::cout << "? 30 1" << std::endl;
			pout->add("? 100 " + to_string(UsbView::getInstance()->getId() ));
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
