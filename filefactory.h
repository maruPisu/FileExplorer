#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include <file.h>
#include <QFileInfo>

class FileFactory
{
public:
    FileFactory();

    static const int DIR = 0;
    static const int NOT_DIR = 1;

    File *getFile(int, QFileInfo);
};

#endif // FILEFACTORY_H
