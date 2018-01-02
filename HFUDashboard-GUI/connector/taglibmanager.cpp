#include "taglibmanager.h"
#include <iostream>
#include <QDebug>
#include "connector/connector.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fileref.h>
#include <tag.h>

TaglibManager::TaglibManager(QObject *parent) :
    QObject(parent)
{
}

void TaglibManager::setFiles(char * files) {
    Connector *creader = Connector::getInstance();
    QVariantList tagList;
    QStringList stringEntrys;
    QStringList titelList;
    QStringList artistList;

    QString path = "";
    QString uri = "";

    std::string filesString(files);
    std::string delimiter = "////";

    // get every entry of string
    size_t pos = 0;
    std::string fileName;
    while ((pos = filesString.find(delimiter)) != std::string::npos)
    {
        fileName = filesString.substr(0, pos);
        stringEntrys.append(QString::fromStdString(fileName));
        filesString.erase(0, pos + delimiter.length());
    }

    // the last enty is the path
    path = stringEntrys.takeLast();

    for (int i = 0; i < stringEntrys.length(); i++)
    {
        // remove identifier DIR: or FILE:
        QStringRef fileIdentifiere(&stringEntrys[i], 0, 4);
        if (fileIdentifiere == "DIR:")
        {
            QString dirName = stringEntrys[i].remove(0, 4);
            titelList.append(dirName);
            artistList.append("");
        }
        else
        {
            QString fileName = stringEntrys[i].remove(0, 5);
            uri = path + "/" + fileName;
            TagLib::FileRef f(const_cast<char*>(uri.toStdString().c_str()));
            TagLib::Tag *tag = f.tag();
            QString title = tag->title().toCString();
            QString artist = tag->artist().toCString();

            if (title.isEmpty())
                titelList.append(fileName);
            else
                titelList.append(title);

            if (artist.isEmpty())
                artistList.append("unknown");
            else
                artistList.append(artist);
        }
    }

    tagList << QVariant(titelList);
    tagList << QVariant(artistList);
    emit creader -> sendNewMusicList(tagList);
}
