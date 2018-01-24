#include "GlobalParams.hpp"
#include <iostream>

using namespace std;

GlobalParams::GlobalParams()
{
	pout = PipeControl::getInstance();
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
	pout->add( "? 14 1" );
}

void GlobalParams::decreaseVolume()
{
	if (volume > 0) {
		volume -= 5;
	}
	player.setVolume((double)volume/100);
	pout->add( "? 13 1" );
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
	pout->add( "* " + fileManager.getMP3Information(*dirContent, getCurrentDirectory()) );
}

bool GlobalParams::previousSelect()
{
	if(currentSelect > 0)
	{
		--currentSelect;
		pout->add( "? 20 -1" );
		return true;
	}
	return false;
}

// Wenn das Wählrad gedreht wird, soll hier hochgezählt werden.
bool GlobalParams::nextSelect()
{
	if(dirContent != nullptr && currentSelect < dirContent->size()-1)
	{
		++currentSelect;
		pout->add( "? 20 1" );
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
			pout->add( "? 22 0" );
		}
		else 
		{
			player.play();
			pout->add( "? 22 1" );
		}
	}
}

// Zum laden es "currentSelect"ten liedes.
void GlobalParams::loadSelection()
{
	// IST MUSIKDATEI???
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
		pout->add( "* " + fileManager.getMP3Information(*dirContent, getCurrentDirectory()) );
	}
	pout->add( "New Directory: " + getCurrentDirectory() );
}

std::string GlobalParams::getCurrentDirectory()
{
	return mountpoint + subDir;
}

void GlobalParams::SecondsHandler(int seconds, int* c_seconds)
{
	// *c_seconds = seconds;
	PipeControl::getInstance()->add( "? 27 " + to_string(seconds) );
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

void GlobalParams::loadPreviousSong()
{
	while(previousSelect())
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
			pout->add( "? 28 1" );
		}
		else if(rate > 1.0)
		{
			player.advancedSeek(rate + 0.5);
		}
		else
		{
			player.advancedSeek(1.0);
			pout->add( "? 28 0" );
		}
	} else if(direction < 0)
	{
		if((int)rate == (int)1.0)
		{
			player.advancedSeek(-2.0);
			pout->add( "? 28 -1" );
		}
		else if(rate < 1.0)
		{
			player.advancedSeek(rate - 0.5);
		}
		else 
		{
			player.advancedSeek(1.0);
			pout->add( "? 28 0" );
		}
	}
	else player.advancedSeek(1.0);
}
