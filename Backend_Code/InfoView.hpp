#ifndef InfoView_hpp
#define InfoView_hpp

#include "StartView.hpp"
#include "UsbView.hpp"
#include <string>
#include <iostream>

class InfoView : public State
{
private:
	InfoView();
	
public:
	static InfoView* getInstance();
	virtual State* sendEvent(EventEnum, GlobalParams&);
	virtual std::string getName();
};


#endif