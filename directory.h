#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <file.h>

class Directory : public File
{
    Q_OBJECT
public:
    Directory(QFileInfo fileName, QWidget *parent = 0);
    ~Directory();

private:
    void mouseDoubleClickEvent( QMouseEvent * e );

signals:
    void doubleClicked(QString);
};

#endif // DIRECTORY_H
