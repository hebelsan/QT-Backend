#include "CarCamView.hpp"

using namespace std;

CarCamView::CarCamView() : State()
{
	pout = PipeControl::getInstance();
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
			//std::cout << "? 4 1" << std::endl;
			pout->add("? 100 " + to_string( InfoView::getInstance()->getId()));
			return InfoView::getInstance();
		case BUTTON_DOWN:
			//std::cout << "? 5 1" << std::endl;
			pout->add("? 100 " + to_string(StartView::getInstance()->getId()));
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
			//std::cout << "? 11 1" << std::endl;
			pout->add("? 100 " + to_string( UsbView::getInstance()->getId() ));
			return UsbView::getInstance();
		case RSB_TOP:
			globals.setOldState(this);
			pout->add("? 100 " + to_string( UsbView::getInstance()->getId() ));
			return UsbView::getInstance();
	}
	return this;
}

std::string CarCamView::getName()
{
	return std::string("Car Cam View");
}

int CarCamView::getId()
{
	return 2;
}