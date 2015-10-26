#include "directory.h"
#include "ui_file.h"
#include <QDebug>

Directory::Directory(QFileInfo fileName, QWidget *parent)
    :File(fileName, parent)
{
    ui->setupUi(this);
    qDebug() << "inizio con";
    QPixmap mypix (":/images/dir.png");
    ui->label->setPixmap(mypix);

    ui->label_filename->setWordWrap(true);
    ui->label_filename->setText(fileName.fileName());

    path = fileName.absoluteFilePath();
    qDebug() << "fine con";
}

Directory::~Directory(){
    delete ui;
}

void Directory::mouseDoubleClickEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton)
    {
        doubleClicked(path);
    }
}
