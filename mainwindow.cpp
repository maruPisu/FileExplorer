#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    row = 0;
    col = 0;

    max_rows = 4;
    max_cols = 4;

    QString path = "/Users/mauropisu/Documents";
    mDir = new QDir(path);

    cleanUp();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cleanUp()
{
    clearLayout();
    col = 0;
    row = 0;
    QFileInfoList fileList = mDir->entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries);
    foreach(QFileInfo mInfo, fileList)
    {
        insertFile(mInfo, row, col, mInfo.isDir());
        if(++col == max_cols)
        {
            col = 0;
            row++;
        }
    }

    QWidget* verticalSpacer = new QWidget();
    verticalSpacer->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
    QWidget* horizontalSpacer = new QWidget();
    horizontalSpacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->file_layout->addWidget(verticalSpacer, max_rows, 0);
    ui->file_layout->addWidget(horizontalSpacer, 0, max_cols);
}

void MainWindow::clearLayout()
{
    int i = 0;
    while (QLayoutItem* item = ui->file_layout->takeAt(i))
    {
        if (QWidget* widget = item->widget())
            delete widget;
        delete item;
    }
}

void MainWindow::insertFile(QFileInfo fileInfo, int x, int y, bool isDir)
{
    mFile = new File(fileInfo, isDir);
    ui->file_layout->addWidget(mFile, x, y);

    connect(mFile, SIGNAL(doubleClicked(QString)), this, SLOT(dirDoubleClicked(QString)));
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
//   qDebug() << QString::number(this->width() ) << ", " <<QString::number(this->height() );
}

void MainWindow::on_toolButton_clicked()
{
    mDir->cdUp();
    cleanUp();
}

void MainWindow::dirDoubleClicked(QString newPath)
{
    mDir = new QDir(newPath);
    cleanUp();
}
