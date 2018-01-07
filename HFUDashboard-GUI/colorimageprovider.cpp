#include "colorimageprovider.h"

bool ColorImageProvider::instanceflag = false;
ColorImageProvider* ColorImageProvider::instance = NULL;

QImage ColorImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = 100;
    int height = 100;

    QImage result;

    if (titleCovers.isEmpty())
    {
        QImage *standartTitleCover = new QImage(":/bilder/UsbView/NotenSchluessel.jpg");
        if (requestedSize.isValid())
        {
            result = standartTitleCover->scaled(requestedSize, Qt::KeepAspectRatio);
        } else
        {
            result = standartTitleCover->scaled(width, height, Qt::KeepAspectRatio);
        }
        *size = result.size();
        return result;
    }
    else
    {
        QImage cover = titleCovers.value(id);
        if (requestedSize.isValid())
        {
            result = cover.scaled(requestedSize, Qt::KeepAspectRatio);
        } else
        {
            result = cover.scaled(width, height, Qt::KeepAspectRatio);
        }
        *size = result.size();
        return result;
    }
}

void ColorImageProvider::setCovers(QHash<QString, QImage> newCovers)
{
    titleCovers = newCovers;
}

ColorImageProvider* ColorImageProvider::getInstance(){

    if(!instanceflag){
        instanceflag = true;
        instance = new ColorImageProvider();
    }

    return instance;
}
