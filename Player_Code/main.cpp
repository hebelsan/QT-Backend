#include <unistd.h>
#include "GstPlayer.hpp"
#include <iostream>

int main (int argc, char** args)
{
	GstPlayer player(argc, args);
	std::cout<< player.isLoaded() << std::endl;
	player.open("file:///home/jonathanweissenberger/Downloads/01 here we go.mp3");
	std::cout<< player.isLoaded() << std::endl;
	player.play();
	usleep(5000000);
	
	player.pause();
	usleep(400000);
	player.play();
	usleep(9000000);
	player.setVolume(0.4);
	player.advancedSeek(3);
	usleep(100000);
	while(player.isPlaying());
	std::cout << "Loading file 2 ..." << std::endl;
	player.open("file:///home/jonathanweissenberger/Downloads/Test.mp3");
	usleep(400000);
	player.play();
	usleep(400000);
	std::cout << player.getDuration()<< std::endl;
	player.pause();
	usleep(500000);
	player.play();
	player.join();
	return 1;
}
