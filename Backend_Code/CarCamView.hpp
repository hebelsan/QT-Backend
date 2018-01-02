#ifndef CarCamView_HPP
#define CarCamView_HPP

#include <string>
#include "State.hpp"
#include "GlobalParams.hpp"
#include "InfoView.hpp"
#include "StartView.hpp"

class CarCamView : public State
{
private:
	CarCamView();
	
public:
	static CarCamView* getInstance();
	virtual State* sendEvent(EventEnum, GlobalParams&);
	virtual std::string getName();
};

#endif