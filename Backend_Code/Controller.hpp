#ifndef __CONTROLLER_HPP_INCLUDED__
#define __CONTROLLER_HPP_INCLUDED__

#include <string>
#include "ControllerDatentypen.hpp"
#include "StartView.hpp"
#include "UsbView.hpp"

class Controller {
	private:
	struct state systemState;
	Controller();
	GstPlayer player = GstPlayer(0, NULL);
	StartView startView;
	UsbView usbView;

	public:
	static Controller *getInstance();
	MainViewEnum getMainView();
	LeftViewEnum getLeftView();
	double getPlayerVolume();
	void setMainView(MainViewEnum);
	void setLeftView(LeftViewEnum);
	void setSystemstate(state);

	void sendEvent(EventEnum);
};

#endif
