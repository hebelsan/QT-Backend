#include "FileManager.hpp"
#include <iostream>
#include <string>

#include <unistd.h>

using namespace std;

int main()
{
	string filesString = "";
	FileManager f;
	vector<string>* files = f.getDirContent("/home/jonathanweissenberger");
	for (int i=0; i<files->size(); i++) 
	{
		if (i != (files->size() -1))   
        		filesString += (*files)[i] + "////";
		else 
			filesString += (*files)[i];
	}
	//usleep(5000000);
	cout << "* " << filesString << endl << endl;
	cout << f.getContentString(*files)<< endl;
	cout << "List content " << (*files)[1] << " is File: " << f.isFile((*files)[1])<< endl;
	string dir = "hallo/welt";
	f.cropDir(dir);
	cout << dir << endl;
}
