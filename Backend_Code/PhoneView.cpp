#include "PhoneView.hpp"

PhoneView* PhoneView::getInstance()
{
	static PhoneView theInstance;
	return &theInstance;
}

std::string PhoneView::getName()
{
	return std::string("Phone View");
}

State* PhoneView::sendEvent(EventEnum event, GlobalParams& globals)
{
	switch(event)
	{
		case BUTTON_UP:
			return StartView::getInstance();
			break;
		case BUTTON_DOWN:
			return InfoView::getInstance();
			break;
		case BUTTON_A:
			//Volume DOWN
			globals.decreaseVolume();
			
			break;
		case BUTTON_Y:
			// Volume UP
			globals.increaseVolume();
			// std::cout << "? 14 " << control_daten->b << std::endl;
			break;
		case USB_PLUGGED_IN:
			globals.setOldState(this);
			return UsbView::getInstance();
			break;
	}
	return this;
}