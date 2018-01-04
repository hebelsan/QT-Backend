#include <dirent.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

#include <fileref.h>
#include <tag.h>
#include "FileManager.hpp"
using namespace std;

bool sortFunction(string content1, string content2);

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
			} else if ((fileName[0] != '.') || fileName == ".." /* && (fileName != "..")*/)
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
	std::sort(fileNames->begin(), fileNames->end(), sortFunction);
	return fileNames;
}

string FileManager::getContentString(vector<string>& content)
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
	if(file.substr(0,4) == "DIR:")
		return file.substr(4);
	else return file.substr(5);
}

bool sortFunction(string content1, string content2)
{
	content1 = FileManager::removePrefix(content1);
	content2 = FileManager::removePrefix(content2);
	if(content1 == "..") return 1;
	else if(content2 == "..") return 0;
	return content1.compare(content2) < 0;
}