#include "FileManager.hpp"
#include <iostream>
#include <string>

#include <unistd.h>

using namespace std;

int main()
{
	string filesString = "";
	FileManager f;
	vector <string> files = f.getFileNames("/home/alex/Music");
	for (int i=0; i<files.size(); i++) 
	{
		if (i != (files.size() -1))   
        		filesString += files[i] + "////";
		else 
			filesString += files[i];
	}
	usleep(5000000);
	cout << "* " << filesString << endl;
}
