#include "Controller.hpp"
#include "ControllerDatentypen.hpp"
#include <iostream>
#include <string>
#include <regex>

static EventEnum toEventEnum(std::string, bool&, std::regex&);

int main (int argc, char** argv)
{
	std::string regexp = "^[udMmsnpvVrR](\\s(([a-z^:/?#]+)://)?(/(/?[a-zA-Z0-9]+(\\\\\\s)*)+))?\\r?\\n?";
	std::regex validator(regexp);
	Controller *c = Controller::getInstance();
	bool run = true;

	std::cout << "### Controller --- Testprogramm ###"<< std::endl;
	std::string text;
	
	std::cout << std::regex_match("m /home/jonathanweissenberger", validator) << std::endl;
	
	for(;run;)
	{
		std::cout << c->getCurrentState()->getName() << std::endl;
		std::getline(std::cin, text);
		c->sendEvent(toEventEnum(text, run, validator));
	}
	return 1;
}

static EventEnum toEventEnum(std::string text, bool& run, std::regex& validator)
{
	if(std::regex_match(text, validator))
	{
		switch(text[0])
		{
			case 'u':
			case 'U':
				// up
				return BUTTON_UP;
			case 'd':
			case 'D':
				// down
				return BUTTON_DOWN;
			case 'm':
				// mounted
				if(text.length() > 1)
				{
					std::string uri = text.substr(2);
					std::cout << uri << std::endl;
					Controller::getInstance()->setMountpoint(uri);
				}
				return USB_PLUGGED_IN;
			case 'M':
				// unmounted
				return USB_PLUGGED_OUT;
			case 's':
				// select
				return WHEEL_PRESSED;
			case 'n':
				// next
				return WHEEL_TURN_R;
			case 'p':
				// previous
				return WHEEL_TURN_L;
			case 'v':
				return BUTTON_A;
			case 'V':
				return BUTTON_Y;
			case 'r':
				return WHEEL_DIR_R;
			case 'R':
				return WHEEL_DIR_L;
		}
	}
	else 
	{
		std::cout << "Ungültige Eingabe! Aborting... " << std::endl;
		// run = false;
	}
	return NOTHING;
}
