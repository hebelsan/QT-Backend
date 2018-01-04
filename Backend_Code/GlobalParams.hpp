#ifndef GlobalParams_HPP
#define GlobalParams_HPP

#include <string>
#include "State.hpp"

class GlobalParams
{
private:
	std::string currentPlayFile;
	std::string subDir;
	std::vector<std::string>* dirContent;
	int seconds;
	int oldSeconds;
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
	bool nextSelect();
	void previousSelect();
	void loadSelection();
	void togglePlayer();
	std::string getCurrentDirectory();
	static void SecondsHandler(int, int*);
	static void EofHandler(GlobalParams*);
	void loadNextSong();
	void seek(int);
};

#endif
