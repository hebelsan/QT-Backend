#ifndef __CONTROLLERDATENTYPEN_HPP_INCLUDED__
#define __CONTROLLERDATENTYPEN_HPP_INCLUDED__

#include <string>

enum MainViewEnum 
{ 
	START_VIEW, 
	USB_VIEW 
};

enum LeftViewEnum
{ 
	MEDIA, 
	NAV, 
	INFO, 
	PHONE, 
	endEnum 
};
enum EventEnum 
{ 
	BUTTON_UP, BUTTON_DOWN, BUTTON_LEFT, BUTTON_RIGHT,
	RSB_TOP, BUTTON_A, BUTTON_Y, 
	WHEEL_TURN,
	WHEEL_PRESSED, WHEEL_DIRECTION,
	USB_PLUGGED_IN, USB_PLUGGED_OUT 
};

struct AudioState {
	bool isPlaying;
	bool isPaused;
	int volume;
	std::string currentTitle;
};

struct state { 
	MainViewEnum mainView;
	LeftViewEnum leftView;
	AudioState audioState;
};

#endif
