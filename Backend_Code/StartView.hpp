#ifndef StartView_HPP
#define StartView_HPP

#include "State.hpp"

class StartView : public State 
{
	public:
	StartView() : State(){}
	void sendEvent(EventEnum, struct state *, GstPlayer *) const;
};

#endif
