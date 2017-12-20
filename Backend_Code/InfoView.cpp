#include "InfoView.hpp"

InfoView::InfoView()
{}

InfoView* InfoView::getInstance()
{
	static InfoView theInstance;
	return &theInstance;
}

std::string InfoView::getName()
{
	return std::string("Info View");
}

State* InfoView::sendEvent(EventEnum event, GlobalParams& globals)
{
	switch(event)
	{
		case BUTTON_UP:
			return PhoneView::getInstance();
		case BUTTON_DOWN:
			return CarCamView::getInstance();
		case BUTTON_A:
			//Volume DOWN
			globals.decreaseVolume();
			break;
		case BUTTON_Y:
			// Volume UP
			globals.increaseVolume();
			break;
		case USB_PLUGGED_IN:
			globals.setOldState(this);
			return UsbView::getInstance();
	}
	
	return this;
}