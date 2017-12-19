#include "taglibmanager.h"
#include "connector.h"
#include <iostream>
#include <QDebug>

void TaglibManager::setFiles(char * files) {
    Connector *creader = Connector::getInstance();

    std::string filesString(files);
    std::string delimiter = "////";

    size_t pos = 0;
    std::string fileName;
    while ((pos = filesString.find(delimiter)) != std::string::npos) {
        fileName = filesString.substr(0, pos);
        filesArray.push_back(QString::fromStdString(fileName));
        filesString.erase(0, pos + delimiter.length());
    }

    emit creader-> newMusicTitleList(filesArray);
}
