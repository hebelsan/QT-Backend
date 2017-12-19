#include <dirent.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

#include <fileref.h>
#include <tag.h>
using namespace std;

int main()
{
	DIR *hdir;
	struct dirent *entry;
	string path = "/home/alex/Music";

	TagLib::Tag *tag;
	TagLib::AudioProperties *properties;
	
	struct stat status;

	vector <string> mp3FileNames;
	vector <string> direcotryNames;

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
      			cout << "-- TAG (basic) --" << endl;
      			cout << "title   - \"" << tag->title()   << "\"" << endl;
      			cout << "artist  - \"" << tag->artist()  << "\"" << endl;
      			cout << "album   - \"" << tag->album()   << "\"" << endl;
      			cout << "year    - \"" << tag->year()    << "\"" << endl;
      			cout << "track   - \"" << tag->track()   << "\"" << endl;
      			cout << "genre   - \"" << tag->genre()   << "\"" << endl;
				}
				mp3FileNames.push_back(fileName);
			} else if ((fileName != ".") && (fileName != ".."))
			{
				if ( stat(uri.c_str(), &status) == 0 ) 
				{
					if( status.st_mode & S_IFDIR )
    				{
        				cout << "directory: " << fileName << endl;
						direcotryNames.push_back(fileName);
    				}
				}
        	}
		}
    } while (entry);
    closedir(hdir);

	for (int i=0; i<mp3FileNames.size(); i++)    
        cout << mp3FileNames[i] << "\n";
	for (int i=0; i<direcotryNames.size(); i++)    
        cout << direcotryNames[i] << "\n";
	
}
