#include "filefactory.h"
#include <directory.h>
#include <notdir.h>

FileFactory::FileFactory()
{

}

File *FileFactory::getFile(int type, QFileInfo path)
{
    switch(type)
    {
    case DIR:
        return new Directory(path);
        break;
    case NOT_DIR:
        return new NotDir(path);
    }
    return NULL;
}

