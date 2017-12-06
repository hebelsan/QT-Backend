#include <unistd.h>
#include "GstPlayer.hpp"
#include <iostream>

int main (int argc, char** args)
{
	GstPlayer player(argc, args);
	player.open("file:///home/jonathanweissenberger/Downloads/Test.mp3");
	player.play();
	usleep(5000000);
	
	player.pause();
	usleep(400000);
	player.play();
	player.join();
	return 1;
}
