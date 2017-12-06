#include <unistd.h>
#include "GstPlayer.hpp"
#include <iostream>

int main (int argc, char** args)
{
	GstPlayer player(argc, args);
	player.open("file:///home/pi/test.mp3");
	player.play();
	usleep(5000000);
	
	player.pause();
	usleep(400000);
	player.play();
	usleep(9000000);
	for(int i=0; i< 10; ++i)
	{
		player.setVolume(0.1);
		usleep(1000000);
		player.setVolume(1.0);
		usleep(1000000);
	}
	
	std::cout << player.getDuration()<< std::endl;
	player.join();
	return 1;
}
