#ifndef FileManager_HPP
#define FileManager_HPP

#include <vector>
#include <algorithm>
#include <string>

class FileManager
{
private:

public:
	std::vector<std::string>* getDirContent(std::string path);
	std::string getContentString(std::vector<std::string>&);
	bool isFile(std::string content);
	void cropDir(std::string& dir);
	static std::string removePrefix(std::string);
};


#endif