#include <dirent.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

#include <fileref.h>
#include <tag.h>
#include "FileManager.hpp"
using namespace std;

vector <string> FileManager::getFileNames(std::string _path) {
	DIR *hdir;
	struct dirent *entry;
	string path = _path;
	vector <string> fileNames;

	TagLib::Tag *tag;
	TagLib::AudioProperties *properties;
	
	struct stat status;
    hdir = opendir(path.c_str());

    do
    {
        entry = readdir(hdir);
        if (entry)
        {
			string fileName = string(entry->d_name);
			string uri = path + "/" + fileName;
			TagLib::FileRef f(const_cast<char*>(uri.c_str()));

			if(!f.isNull() && f.tag() && f.audioProperties()) 
			{
      			TagLib::Tag *tag = f.tag();
				properties = f.audioProperties();				
				if (properties->length() > 0) 
				{
					fileNames.push_back(fileName);
				}
			} else if ((fileName != ".") && (fileName != ".."))
			{
				if ( stat(uri.c_str(), &status) == 0 ) 
				{
					if( status.st_mode & S_IFDIR )
    				{
						fileNames.push_back(fileName);
    				}
				}
        	}
		}
    } while (entry);
    closedir(hdir);

	return fileNames;
}
