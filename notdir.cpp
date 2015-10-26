#include "notdir.h"
#include "ui_file.h"

NotDir::NotDir(QFileInfo fileName, QWidget *parent)
    :File(fileName, parent)
{
    ui->setupUi(this);

    QPixmap mypix (":/images/txt.png");
    ui->label->setPixmap(mypix);

    ui->label_filename->setWordWrap(true);
    ui->label_filename->setText(fileName.fileName());

    path = fileName.absoluteFilePath();
}

NotDir::~NotDir(){
    delete ui;
}

void NotDir::mouseDoubleClickEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton)
    {
        doubleClicked(path);
    }
}
