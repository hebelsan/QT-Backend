#ifndef USBVIEW_HPP
#define USBVIEW_HPP

#include "State.hpp"

class UsbView : public State {
	public:
	UsbView() : State(){}
	void sendEvent(EventEnum, struct state*, GstPlayer*) const;
};

#endif
