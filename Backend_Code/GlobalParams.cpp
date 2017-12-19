#include "State.hpp"

GlobalParams::GlobalParams()
{
	volume = 100;
	
}

void GlobalParams::increaseVolume()
{
	if (volume < 100) {
		volume += 5;
	}
	player.setVolume((double)volume/100);
}

void GlobalParams::decreaseVolume()
{
	if (volume > 0) {
		volume -= 5;
	}
	player.setVolume((double)volume/100);
}

unsigned int GlobalParams::getVolume()
{
	return volume;
}

void GlobalParams::setOldState(State* s)
{
	oldState = s;
}

State* GlobalParams::getOldState()
{
	return oldState;
}

std::string GlobalParams::getMountpoint()
{
	return mountpoint;
}

void GlobalParams::setMountpoint(std::string point)
{
	mountpoint = point;
}