#ifndef __CONTROLLER_HPP_INCLUDED__
#define __CONTROLLER_HPP_INCLUDED__

#include <string>
#include "ControllerDatentypen.hpp"
#include "State.hpp"
#include "StartView.hpp"

class Controller {
private:
	Controller();
	GstPlayer player = GstPlayer(0, NULL);
	State *currentState;
	GlobalParams globals;
	
public:
	static Controller *getInstance();
	void sendEvent(EventEnum);
	void setMountpoint(std::string);
	State* getCurrentState();
};

#endif
