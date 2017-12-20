#include "taglibmanager.h"
#include <iostream>
#include <QDebug>
#include "connector/connector.h"

TaglibManager::TaglibManager(QObject *parent) :
    QObject(parent)
{
}

void TaglibManager::setFiles(char * files) {
    Connector *creader = Connector::getInstance();
    QVariantList l;
    QStringList stringList;

    std::string filesString(files);
    std::string delimiter = "////";

    size_t pos = 0;
    std::string fileName;
    while ((pos = filesString.find(delimiter)) != std::string::npos) {
        fileName = filesString.substr(0, pos);
        stringList.append(QString::fromStdString(fileName));
        filesString.erase(0, pos + delimiter.length());
    }

    l << QVariant(stringList);
    setImagesPathsLists(l);
    emit creader -> sendNewMusicList(l);
}
