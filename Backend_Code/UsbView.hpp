#ifndef USBVIEW_HPP
#define USBVIEW_HPP

#include "State.hpp"
#include <string>
#include "StartView.hpp"

class UsbView : public State {
private:
	UsbView();
	
public:
	static State* getInstance();
	virtual State* sendEvent(EventEnum, GlobalParams&);
	virtual std::string getName();
	virtual int getId();
};

#endif
