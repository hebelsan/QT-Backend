#ifndef STATE_HPP
#define STATE_HPP

#include "ControllerDatentypen.hpp"
#include "GstPlayer.hpp"
#include <string>

/*
 * Was ich brauche:
 * Vorgängerstatus,
 * globale bindings.
 * 
 */
class GlobalParams;

class State {
	public:
	State(){};
	virtual State* sendEvent(EventEnum, GlobalParams&) = 0; // sends Event based on view
	virtual std::string getName() = 0;
};

class GlobalParams
{
private:
	unsigned int volume;
	State* oldState;
	GstPlayer player = GstPlayer(0, NULL);
	std::string mountpoint;
	
public:
	GlobalParams();
	void increaseVolume();
	void decreaseVolume();
	unsigned int getVolume();
	void setOldState(State*);
	State* getOldState();
	void setMountpoint(std::string);
	std::string getMountpoint();
};

#endif
