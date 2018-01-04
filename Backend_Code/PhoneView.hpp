#ifndef PhoneView_HPP
#define PhoneView_HPP

#include <string>
#include "State.hpp"
#include "StartView.hpp"
#include "InfoView.hpp"

class PhoneView : public State
{
private:
	PhoneView() : State() {};
public:
	
	static PhoneView* getInstance();
	virtual State* sendEvent(EventEnum, GlobalParams&);
	virtual std::string getName();
	virtual int getId();
};

#endif