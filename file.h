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
    explicit File(QFileInfo fileName, QWidget *parent = 0)
        : QWidget(parent){ path = fileName.absoluteFilePath();}

protected:
    QString path;
    Ui::File *ui;

private:
    virtual void mouseDoubleClickEvent( QMouseEvent * e ) = 0;

signals:
    void doubleClicked(QString);
};

#endif // FILE_H
