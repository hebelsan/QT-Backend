#include "FileManager.hpp"

#include <dirent.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include <fileref.h>
#include <tag.h>
#include <cstring>
#include<id3v2tag.h>
#include<mpegfile.h>
#include<id3v2frame.h>
#include<id3v2header.h>
#include <attachedpictureframe.h>

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

std::string FileManager::getMP3Information(std::vector<string> filesInString, std::string path) {

    vector <string> titelList;
    vector <string> artistList;
    vector <int> titleLengthSeconds;
    // QHash<QString, QImage> titleCovers;
    vector <string> coverIds;

    std::string uri = "";

    for (int i = 0; i < filesInString.size(); i++)
    {
        // remove identifier DIR: or FILE:
        if (!isFile(filesInString[i])) // DIRECTORY
        {
            std::string dirName = removePrefix(filesInString[i]);
            titelList.push_back(dirName);
            artistList.push_back("");
            titleLengthSeconds.push_back((int)0);
			coverIds.push_back("D");
        }
        else
        {
            std::string fileName = removePrefix(filesInString[i]);
            uri = path + "/" + fileName;
            TagLib::FileRef f(const_cast<char*>(uri.c_str()));
            TagLib::AudioProperties *properties = f.audioProperties();
            TagLib::Tag *tag = f.tag();
            std::string title = tag->title().toCString();
            std::string artist = tag->artist().toCString();
            int seconds = properties->length();
            titleLengthSeconds.push_back((int)seconds);

            // append title
            if (title.empty())
            {
                titelList.push_back(fileName);
            } else
            {
                titelList.push_back(title);
            }

            // append artist
            if (artist.empty())
            {
                artistList.push_back("unknown");
            } else
            {
                artistList.push_back(artist);
            }
            // Append cover art
            coverIds.push_back(readCoverArt(uri, titelList.back()));
        }
    }

    std::string result;
	for (int i = 0; i < filesInString.size(); i++) 
	{
		result += titelList[i] + "||||" + artistList[i] + "||||" + std::to_string(titleLengthSeconds[i]) + "||||"+ coverIds[i] + "||||"+ "////";
	}
	return result;
}

// Returns whether Cover available (A for available) or not (M for missing)
string FileManager::readCoverArt(string uri, string name)
{
	TagLib::MPEG::File file(const_cast<char*>(uri.c_str()));
	TagLib::ID3v2::Tag *m_tag = file.ID3v2Tag(true);
	TagLib::ID3v2::FrameList frameList = m_tag->frameList("APIC");

	if(frameList.isEmpty())
	{
		// FALLS KEIN COVER VORHANDEN
		return "M";
	} else
	{
		
		FILE *jpegFile;
		jpegFile = fopen(("/tmp/QTCovers/" + name).c_str(),"wb");
		unsigned long size;
		TagLib::ID3v2::AttachedPictureFrame *PicFrame;
		void *RetImage = NULL, *SrcImage;
		
		for(TagLib::ID3v2::FrameList::ConstIterator it = frameList.begin(); it != frameList.end(); ++it)
		{
			PicFrame = (TagLib::ID3v2::AttachedPictureFrame *)(*it) ;
			// extract image (in it’s compressed form)
			size = PicFrame->picture().size() ;
			SrcImage = malloc ( size ) ;
			if ( SrcImage )
			{
				memcpy ( SrcImage, PicFrame->picture().data(), size ) ;
				fwrite(SrcImage, size, 1, jpegFile);
				fclose(jpegFile);
				free( SrcImage ) ;
			}
		}
		
		TagLib::ID3v2::AttachedPictureFrame *coverImg = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());
		return "A";
	}
}