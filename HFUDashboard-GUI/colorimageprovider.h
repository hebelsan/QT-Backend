#ifndef COLORIMAGEPROVIDER_H
#define COLORIMAGEPROVIDER_H

#include <QtCore>
#include <QImage>
#include <QPainter>
#include <qquickimageprovider.h>

class ColorImageProvider : public QQuickImageProvider
{
private:
    static bool instanceflag;
    static ColorImageProvider *instance;
    QHash<QString, QImage> titleCovers;
public:
    ColorImageProvider()
        : QQuickImageProvider(QQuickImageProvider::Image) {}
    static ColorImageProvider* getInstance();
    ImageType imageType(){
        return QQmlImageProviderBase::Image;
    }
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    void setCovers(QHash<QString, QImage> titleCovers);
};

#endif // COLORIMAGEPROVIDER_H
