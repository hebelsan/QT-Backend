#ifndef TAGLIBMANAGER_H
#define TAGLIBMANAGER_H

#include <QtCore>

class TaglibManager :  public QObject {
    Q_OBJECT
    QStringList filesArray;
public:
    explicit TaglibManager(QObject *parent = 0);
    Q_INVOKABLE void setFiles(char *);
private:
    QVariantList m_imagesPathsLists;
};

#endif // TAGLIBMANAGER_H
