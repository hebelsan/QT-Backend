#include "CarCamView.hpp"

CarCamView::CarCamView() : State()
{
}

CarCamView* CarCamView::getInstance()
{
	static CarCamView theInstance;
	return &theInstance;
}

State* CarCamView::sendEvent(EventEnum event, GlobalParams& globals)
{
	switch(event)
	{
		case BUTTON_UP:
			return InfoView::getInstance();
		case BUTTON_DOWN:
			return StartView::getInstance();
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

std::string CarCamView::getName()
{
	return std::string("Car Cam View");
}