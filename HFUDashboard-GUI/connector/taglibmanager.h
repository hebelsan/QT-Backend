#ifndef TAGLIBMANAGER_H
#define TAGLIBMANAGER_H

#include <QtCore>

class TaglibManager :  public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList imagesPathsLists MEMBER m_imagesPathsLists READ imagesPathsLists WRITE setImagesPathsLists NOTIFY lChanged)
    QStringList filesArray;
public:
    explicit TaglibManager(QObject *parent = 0);
    Q_INVOKABLE void setFiles(char *);
    QVariantList imagesPathsLists() const {
        return m_imagesPathsLists;
    }
    void setImagesPathsLists(QVariantList l) {
        m_imagesPathsLists = l;
        this-> lChanged(l);
    }
    static TaglibManager* getInstance();
signals:
    void lChanged(QVariantList);
private:
    QVariantList m_imagesPathsLists;
    static TaglibManager *instance;
    static bool instanceflag;
};

#endif // TAGLIBMANAGER_H
