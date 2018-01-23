#include "PhoneView.hpp"

using namespace std;

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
			//cout << "? 4 1" << endl;
			pout->add( "? 100 " + to_string(StartView::getInstance()->getId() ));
			return StartView::getInstance();
			break;
		case BUTTON_DOWN:
			//cout << "? 5 1" << endl;
			pout->add( "? 100 " + to_string(InfoView::getInstance()->getId() ));
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
			//cout << "? 11 1" << endl;
			pout->add( "? 100 " + to_string(UsbView::getInstance()->getId() ));
			return UsbView::getInstance();
			break;
		case RSB_TOP:
			globals.setOldState(this);
			pout->add( "? 100 " + to_string(UsbView::getInstance()->getId() ));
			return UsbView::getInstance();
			
	}
	return this;
}

int PhoneView::getId()
{
	return 4;
}