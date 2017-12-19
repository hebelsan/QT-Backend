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
		case USB_PLUGGED_IN:
			globals.setOldState(this);
			return UsbView::getInstance();
			break;
	}
	return this;
}