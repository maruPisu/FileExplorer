#include "file.h"
#include "ui_file.h"

File::File(QFileInfo fileName, bool _isDir, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::File)
{
    ui->setupUi(this);

    isDir = _isDir;
    if(isDir)
    {
        QPixmap mypix (":/images/dir.png");
        ui->label->setPixmap(mypix);
    }
    ui->label_filename->setWordWrap(true);
    ui->label_filename->setText(fileName.fileName());

    path = fileName.absoluteFilePath();
}

File::~File()
{
    delete ui;
}

void File::mouseDoubleClickEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton && isDir)
    {
        doubleClicked(path);
    }
}
