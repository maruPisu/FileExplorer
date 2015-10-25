#ifndef FILE_H
#define FILE_H

#include <QWidget>
#include <QFileInfo>
#include <QMouseEvent>

namespace Ui {
class File;
}

class File : public QWidget
{
    Q_OBJECT

public:
    explicit File(QFileInfo fileName, bool, QWidget *parent = 0);
    ~File();

private:
    Ui::File *ui;
    void mouseDoubleClickEvent( QMouseEvent * e );

    QString path;
    bool isDir;

signals:
    void doubleClicked(QString);
};

#endif // FILE_H
