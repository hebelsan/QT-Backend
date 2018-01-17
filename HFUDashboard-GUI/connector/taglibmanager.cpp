#include "taglibmanager.h"
#include <iostream>
#include <QDebug>
#include "connector/connector.h"
#include "colorimageprovider.h"
#include "QVector"

//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fileref.h>
//#include <tag.h>
//#include<id3v2tag.h>
//#include<mpegfile.h>
//#include<id3v2frame.h>
//#include<id3v2header.h>
//#include <attachedpictureframe.h>

TaglibManager::TaglibManager(QObject *parent) :
    QObject(parent)
{
}

void TaglibManager::setFiles(char * files) {
    Connector *creader = Connector::getInstance();
    ColorImageProvider *musicCoverConnector = ColorImageProvider::getInstance();
    QVariantList tagList;
    QStringList stringEntrys;
    QStringList titelList;
    QStringList artistList;
    QList<QVariant> titleLengthSeconds;
    QHash<QString, QImage> titleCovers;
    QStringList coverIds;

    QString path = "";
    QString uri = "";

    std::string filesString(files);
    std::string delimiter = "////";

    // get every entry of string
//    size_t pos = 0;
//    std::string fileName;
//    while ((pos = filesString.find(delimiter)) != std::string::npos)
//    {
//        fileName = filesString.substr(0, pos);
//        stringEntrys.append(QString::fromStdString(fileName));
//        filesString.erase(0, pos + delimiter.length());
//    }

//    // the last enty is the path
//    path = stringEntrys.takeLast();

//    for (int i = 0; i < stringEntrys.length(); i++)
//    {
//        // remove identifier DIR: or FILE:
//        QStringRef fileIdentifiere(&stringEntrys[i], 0, 4);
//        if (fileIdentifiere == "DIR:")
//        {
//            QString dirName = stringEntrys[i].remove(0, 4);
//            titelList.append(dirName);
//            artistList.append("");
//            titleLengthSeconds.append((int)0);
//            QImage *dirCover = new QImage(":/bilder/UsbView/Directory.png");
//            titleCovers.insert("DIR", *dirCover);
//            coverIds.append("DIR");
//        }
//        else
//        {
//            QString fileName = stringEntrys[i].remove(0, 5);
//            uri = path + "/" + fileName;
//            TagLib::FileRef f(const_cast<char*>(uri.toStdString().c_str()));
//            TagLib::AudioProperties *properties = f.audioProperties();
//            TagLib::Tag *tag = f.tag();
//            QString title = tag->title().toCString();
//            QString artist = tag->artist().toCString();
//            int seconds = properties->length();
//            titleLengthSeconds.append((int)seconds);

//            // append title
//            if (title.isEmpty())
//            {
//                titelList.append(fileName);
//            } else
//            {
//                titelList.append(title);
//            }

//            // append artist
//            if (artist.isEmpty())
//            {
//                artistList.append("unknown");
//            } else
//            {
//                artistList.append(artist);
//            }

//            // append cover
//            TagLib::MPEG::File file(const_cast<char*>(uri.toStdString().c_str()));
//            TagLib::ID3v2::Tag *m_tag = file.ID3v2Tag(true);
//            TagLib::ID3v2::FrameList frameList = m_tag->frameList("APIC");

//            if(frameList.isEmpty())
//            {
//                QImage *standartTitleCover = new QImage(":/bilder/UsbView/NotenSchluessel.jpg");
//                titleCovers.insert(titelList.at(i) + artistList.at(i), *standartTitleCover);
//                coverIds.append(titelList.at(i) + artistList.at(i));
//            } else
//            {
//                TagLib::ID3v2::AttachedPictureFrame *coverImg = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());
//                QImage coverQImg;
//                coverQImg.loadFromData((const uchar *) coverImg->picture().data(), coverImg->picture().size());
//                titleCovers.insert(titelList.at(i) + artistList.at(i), coverQImg);
//                coverIds.append(titelList.at(i) + artistList.at(i));
//            }
//        }
//    }

    musicCoverConnector->setCovers(titleCovers);

    tagList << QVariant(titelList);
    tagList << QVariant(artistList);
    tagList << QVariant(titleLengthSeconds);
    tagList << QVariant(coverIds);
    emit creader -> sendNewMusicList(tagList);
}

void TaglibManager::deliverUsbViewInformation(char *files) {
    Connector *creader = Connector::getInstance();
    ColorImageProvider *musicCoverConnector = ColorImageProvider::getInstance();
    QVariantList informationList;
    QVector <std::string> filesInString;
    QStringList titelList;
    QStringList artistList;
    QList<QVariant> titleLengthSeconds;
    //QHash<QString, QImage> titleCovers;
    QStringList coverIds;

    std::string filesString(files);
    std::string delimiter1 = "////";
    std::string delimiter2 = "||||";

    // get every entry of string
    size_t pos = 0;
    std::string fileName;
    while ((pos = filesString.find(delimiter1)) != std::string::npos)
    {
        fileName = filesString.substr(0, pos);
        filesInString.push_back(fileName);
        filesString.erase(0, pos + delimiter1.length());
    }


    for (int i = 0; i < filesInString.length(); i++) {
        qInfo(filesInString[i].c_str());
    }

    for (int i = 0; i < filesInString.size(); i++) {
        QStringList info;
        while ((pos = filesInString[i].find(delimiter2)) != std::string::npos)
        {
            fileName = filesInString[i].substr(0, pos);
            info.append(QString::fromStdString(fileName));
            filesInString[i].erase(0, pos + delimiter1.length());
        }
        titelList.append(info.at(0));
        artistList.append(info.at(1));
        titleLengthSeconds.append(info.at(2).toInt());
        if (info.at(1).isEmpty()) {
            coverIds.append("Directory");
        } else {
            coverIds.append("Music");
        }
    }

    // musicCoverConnector->setCovers(titleCovers);

    informationList << QVariant(titelList);
    informationList << QVariant(artistList);
    informationList << QVariant(titleLengthSeconds);
    informationList << QVariant(coverIds);
    emit creader -> sendNewMusicList(informationList);
}
