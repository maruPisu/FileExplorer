#ifndef NOTDIR_H
#define NOTDIR_H

#include <file.h>

class NotDir : public File
{
    Q_OBJECT
public:
    NotDir(QFileInfo fileName, QWidget *parent = 0);
    ~NotDir();

private:
    void mouseDoubleClickEvent( QMouseEvent * e );

signals:
    void doubleClicked(QString);
};

#endif // NOTDIR_H
