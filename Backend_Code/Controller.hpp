#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include "GstPlayer.hpp"

enum MainView { START_VIEW, USB_VIEW };
enum LeftView { MEDIA, NAV, INFO, PHONE, endEnum };
enum Event    { BUTTON_UP, BUTTON_DOWN, BUTTON_LEFT, BUTTON_RIGHT,
		RSB_TOP, BUTTON_A, BUTTON_Y, WHEEL_TURN,
		WHEEL_PRESSED, WHEEL_DIRECTION,
		USB_PLUGGED_IN, USB_PLUGGED_OUT };

struct AudioState {
	bool isPlaying;
	bool isPaused;
	double volume;
	std::string currentTitle;
};

struct state { 
	MainView mainView;
	LeftView leftView;
	AudioState audioState;
};

class Controller {
	private:
	struct state systemState;
	Controller();
	GstPlayer player = GstPlayer(0, NULL);

	public:
	static Controller *getInstance();
	MainView getMainView();
	LeftView getLeftView();
	double getPlayerVolume();
	void setMainView(MainView);
	void setLeftView(LeftView);
	void sendEvent(Event);
};

#endif
