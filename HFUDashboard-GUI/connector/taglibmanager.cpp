#include "taglibmanager.h"
#include <iostream>
#include <QDebug>
#include "connector/connector.h"

#include <sys/types.h>
#include <sys/stat.h>
// #include <fileref.h>
#include <tag.h>

TaglibManager::TaglibManager(QObject *parent) :
    QObject(parent)
{
}

void TaglibManager::setFiles(char * files) {
    Connector *creader = Connector::getInstance();
    QVariantList tagList;
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

    // the last enty is the path
    std::string path = stringList.takeLast().toUtf8().constData();
    // qInfo(path);

    tagList << QVariant(stringList);
    emit creader -> sendNewMusicList(tagList);
}
