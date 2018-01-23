#ifndef StartView_HPP
#define StartView_HPP

#include "State.hpp"
#include "CarCamView.hpp"
#include "PhoneView.hpp"
#include "UsbView.hpp"
#include <string>

class StartView : public State 
{
private:
	StartView() : State(){ pout = PipeControl::getInstance(); }
	PipeControl* pout;
	
public:
	static StartView* getInstance();
	virtual State* sendEvent(EventEnum, GlobalParams&);
	virtual std::string getName();
	virtual int getId();
};

#endif
