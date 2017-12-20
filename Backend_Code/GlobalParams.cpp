#include "State.hpp"
#include <iostream>

GlobalParams::GlobalParams()
{
	volume = 100;
	dirContent = nullptr;
	subDir = "";
	currentSelect = 0;
}

void GlobalParams::increaseVolume()
{
	if (volume < 100) {
		volume += 5;
	}
	player.setVolume((double)volume/100);
	std::cout << "? 14 1" << std::endl;
}

void GlobalParams::decreaseVolume()
{
	if (volume > 0) {
		volume -= 5;
	}
	player.setVolume((double)volume/100);
	std::cout << "? 13 1" << std::endl;
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
	if(dirContent != nullptr && currentSelect < dirContent->size()-1)
		++currentSelect;
}

void GlobalParams::togglePlayer()
{
	if(player.isLoaded())
	{
		if(player.isPlaying())
		{
			player.pause();
			std::cout << "? 22 0" << std::endl;
		}
		else 
		{
			player.play();
			std::cout << "? 22 1" << std::endl;
		}
	}
}

// Zum laden es "currentSelect"ten liedes.
void GlobalParams::loadSelection()
{
	if(fileManager.isFile((*dirContent)[currentSelect]))
	{
		
		if(player.isLoaded())
		player.open("file://"+mountpoint+subDir+(*dirContent)[currentSelect]);
		togglePlayer();
	}
	else
	{
		// wenn .. selektiert, dann abwärts bewegen
		if((*dirContent)[currentSelect] == ".." && subDir == "")
			fileManager.cropDir(subDir);
		// aufwärts
		else 
		{
			subDir = subDir + "/" + (*dirContent)[currentSelect];
			delete dirContent;
			dirContent = fileManager.getDirContent(mountpoint + subDir);
		}
	}
}