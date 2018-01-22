#include "InfoView.hpp"

using namespace std;

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
			//cout << "? 4 1" << endl;
			cout << "? 100 " << PhoneView::getInstance()->getId() << endl;
			return PhoneView::getInstance();
		case BUTTON_DOWN:
			//cout << "? 5 1" << endl;
			cout << "? 100 " << CarCamView::getInstance()->getId() << endl;
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
			//cout << "? 11 1" << endl;
			cout << "? 100 " << UsbView::getInstance()->getId() << endl;
			return UsbView::getInstance();
		case RSB_TOP:
			globals.setOldState(this);
			cout << "? 100 " << UsbView::getInstance()->getId() << std::endl;
			return UsbView::getInstance();
	}
	
	return this;
}

int InfoView::getId()
{
	return 3;
}