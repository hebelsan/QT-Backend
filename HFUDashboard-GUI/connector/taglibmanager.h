#ifndef TAGLIBMANAGER_H
#define TAGLIBMANAGER_H

#include <QtCore>
#include <vector>
#include <string>

class TaglibManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString author WRITE setAuthor)
    std::vector <QString> filesArray;
public:
    void setFiles(char *);
};

#endif // TAGLIBMANAGER_H
