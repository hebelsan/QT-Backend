#include "State.hpp"
#include <iostream>

GlobalParams::GlobalParams()
{
	volume = 100;
	dirContent = nullptr;
	subDir = "";
	
}

void GlobalParams::increaseVolume()
{
	if (volume < 100) {
		volume += 5;
	}
	player.setVolume((double)volume/100);
	std::cout << "? 13 1" << std::endl;
}

void GlobalParams::decreaseVolume()
{
	if (volume > 0) {
		volume -= 5;
	}
	player.setVolume((double)volume/100);
	std::cout << "? 14 1" << std::endl;
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
	if(point != "") dirContent = fileManager.getDirContent(mountpoint);
	else return;
	// TODO SEND Dir Information;
	std::cout << "* " << fileManager.getContentString(*dirContent) << std::endl;
}

void GlobalParams::previousSelect()
{
	if(currentSelect > 0)
		--currentSelect;
}

// Wenn das Wählrad gedreht wird, soll hier hochgezählt werden.
void GlobalParams::nextSelect()
{
	if(currentSelect < dirContent->size()-1)
		++currentSelect;
}

// Zum laden es "currentSelect"ten liedes.
void GlobalParams::loadSelection()
{
	if(fileManager.isFile((*dirContent)[currentSelect]))
	{
		// TODO load player;
		// player.open("file://"+mountpoint+subDir+(*dirContent)[currentSelect]);
	}
	else
	{
		if((*dirContent)[currentSelect] == "..")
			fileManager.cropDir(subDir);
		else subDir = subDir + "/" + (*dirContent)[currentSelect];
		
	}
}