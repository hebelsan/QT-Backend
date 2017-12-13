#ifndef STATE_HPP
#define STATE_HPP

#include "ControllerDatentypen.hpp"
#include "GstPlayer.hpp"

class State {
	public:
	State();
	void sendEvent(EventEnum, state) const; // sends Event based on view
};

#endif
