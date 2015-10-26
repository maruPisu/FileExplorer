#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#ifdef _WIN32
   #define ROOT "c:/"
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_MAC
        #define ROOT "/Users"
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    // linux
#elif __unix__
    #define ROOT "/home/"
#   error "Unknown compiler"
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    row = 0;
    col = 0;

    max_rows = 4;
    max_cols = 10;

    isCleaning = false;

    QString path = ROOT;
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

    ui->current_path->setText(mDir->absolutePath());
    QFileInfoList fileList = mDir->entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries);
    setGrid(fileList.size());
    isCleaning = true;
    foreach(QFileInfo mInfo, fileList)
    {
        insertFile(mInfo, row, col, mInfo.isDir());
        if(++col == max_cols)
        {
            col = 0;
            row++;
        }
    }
    isCleaning = false;
    QWidget* verticalSpacer = new QWidget();
    verticalSpacer->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
    QWidget* horizontalSpacer = new QWidget();
    horizontalSpacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->file_layout->addWidget(verticalSpacer, max_rows, 0);
    ui->file_layout->addWidget(horizontalSpacer, 0, max_cols);
}

void MainWindow::setGrid(int num)
{
    if(num < 6)
        max_cols =6;
    if(num > 5 && num < 10)
        max_cols =3;
    if(num > 9 && num < 17)
        max_cols =4;
    if(num > 16 && num < 26)
        max_cols =5;
    if(num > 25)
        max_cols =6;
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
    if(stack.indexOf(mDir->absolutePath()) == -1)
        stack.push_front(mDir->absolutePath());
    mDir->cdUp();
    cleanUp();
}

void MainWindow::dirDoubleClicked(QString newPath)
{
    stack.clear();
    mDir = new QDir(newPath);
    cleanUp();
}

void MainWindow::on_toolButton_2_clicked()
{
    int index = stack.indexOf(mDir->absolutePath()) + 1; // -1 if is not in the stack, it means it will take the 0th element
    if(stack.count() > index)
    {
        mDir = new QDir(stack.at(index));
        cleanUp();
    }

}
