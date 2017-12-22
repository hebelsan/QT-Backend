#include <dirent.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

#include <fileref.h>
#include <tag.h>
#include "FileManager.hpp"
using namespace std;

vector<string>* FileManager::getDirContent(std::string _path) {
	DIR *hdir;
	struct dirent *entry;
	string path = _path;
	vector<string>* fileNames = new vector<string>();

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
					fileNames->push_back("FILE:"+fileName);
				}
			} else if ((fileName != ".") /* && (fileName != "..")*/)
			{
				if ( stat(uri.c_str(), &status) == 0 ) 
				{
					if( status.st_mode & S_IFDIR )
    				{
						fileNames->push_back("DIR:"+ fileName);
    				}
				}
        	}
		}
    } while (entry);
    closedir(hdir);

	return fileNames;
}

std::string FileManager::getContentString(vector<string>& content)
{
	std::string result = "";
	for(std::vector<string>::iterator it = content.begin(); it != content.end(); ++it)
	{
		result = result + *it + "////";
	}
	//result = result.substr(0, result.length()-4);
	return result;
}

bool FileManager::isFile(string content)
{
	return content.substr(0,4) != "DIR:";
}

void FileManager::cropDir(string& dir)
{
	size_t pos = dir.find_last_of('/');
	if(pos != std::string::npos)
	{
		dir = dir.substr(0, pos);
	}
	else dir = "";
}

string FileManager::removePrefix(string file)
{
	return file.substr(5);
}