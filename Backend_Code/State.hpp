#ifndef STATE_HPP
#define STATE_HPP

#include "ControllerDatentypen.hpp"
#include "GstPlayer.hpp"
#include <string>
#include <vector>
#include "FileManager.hpp"

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
	// virtual void enter() = 0;
};

class GlobalParams
{
private:
	std::string subDir;
	std::vector<std::string>* dirContent;
	FileManager fileManager;
	int currentSelect;
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
	void nextSelect();
	void previousSelect();
	void loadSelection();
	void togglePlayer();
};

#endif
