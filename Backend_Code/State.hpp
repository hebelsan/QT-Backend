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
	State();
	virtual State* sendEvent(EventEnum, GlobalParams&) = 0; // sends Event based on view
	virtual std::string getName() = 0;
	virtual int getId() = 0;
	// virtual void enter() = 0;
};

#endif
