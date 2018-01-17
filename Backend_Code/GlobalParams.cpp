#include "GlobalParams.hpp"
#include <iostream>

using namespace std;

GlobalParams::GlobalParams()
{
	currentPlayFile = "";
	volume = 100;
	dirContent = nullptr;
	subDir = "";
	currentSelect = 0;
	player.setSecondsCb((seconds_cb)SecondsHandler, (void*)&seconds);
	player.setEofCb((eof_cb)EofHandler, (void*)this);
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
	std::cout << "* " << fileManager.getMP3Information(*dirContent, getCurrentDirectory()) << std::endl;
}

void GlobalParams::previousSelect()
{
	if(currentSelect > 0)
	{
		--currentSelect;
		std::cout << "? 20 -1" << std::endl;
	}
}

// Wenn das Wählrad gedreht wird, soll hier hochgezählt werden.
bool GlobalParams::nextSelect()
{
	if(dirContent != nullptr && currentSelect < dirContent->size()-1)
	{
		++currentSelect;
		std::cout << "? 20 1" << std::endl;
		return true;
	}
	return false;
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
		std::string uri = "file://"+getCurrentDirectory()+'/'+fileManager.removePrefix((*dirContent)[currentSelect]);
		if(uri != currentPlayFile)
		{
			player.open(uri);
			currentPlayFile = uri;
		}
		togglePlayer();
	}
	else
	{
		// wenn .. selektiert, dann abwärts bewegen
		if((*dirContent)[currentSelect] == "DIR:..")
			fileManager.cropDir(subDir);
		// aufwärts
		else 
		{
			subDir = subDir + "/" + fileManager.removePrefix((*dirContent)[currentSelect]);
		}
		currentSelect = 0;
		delete dirContent;
		dirContent = fileManager.getDirContent(getCurrentDirectory());
		std::cout << "* " << fileManager.getMP3Information(*dirContent, getCurrentDirectory()) << std::endl;
	}
	std::cout << "New Directory: " << getCurrentDirectory() << std::endl;
}

std::string GlobalParams::getCurrentDirectory()
{
	return mountpoint + subDir;
}

void GlobalParams::SecondsHandler(int seconds, int* c_seconds)
{
	// *c_seconds = seconds;
	cout << "? 27 " << seconds << endl;
}

void GlobalParams::EofHandler(GlobalParams* object)
{
	object->loadNextSong();
}

void GlobalParams::loadNextSong()
{
	while(nextSelect())
	{
		if(fileManager.isFile((*dirContent)[currentSelect]))
		{
			loadSelection();
			return;
		}
	}
}

void GlobalParams::seek(int direction)
{
	double rate = player.getPlaybackRate();
	
	if(direction > 0)
	{
		if((int)rate == (int)1.0)
		{
			player.advancedSeek(2.5);
			cout << "? 28 1" << endl;
		}
		else if(rate > 1.0)
		{
			player.advancedSeek(rate + 0.5);
		}
		else
		{
			player.advancedSeek(1.0);
		}
	} else if(direction < 0)
	{
		if((int)rate == (int)1.0)
		{
			player.advancedSeek(-2.0);
			cout << "? 28 -1" << endl;
		}
		else if(rate < 1.0)
		{
			player.advancedSeek(rate - 0.5);
		}
		else 
		{
			player.advancedSeek(1.0);
			cout << "? 28 0" << endl;
		}
	}
	else player.advancedSeek(1.0);
}