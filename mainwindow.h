#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <file.h>
#include <QFileInfo>
#include <QDir>>
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_toolButton_clicked();

private:
    Ui::MainWindow *ui;
    void insertFile(QFileInfo fileName, int, int, bool);
    void cleanUp();
    void resizeEvent(QResizeEvent* event);
    void clearLayout();
    void setGrid(int num);

    QDir *mDir;
    File *mFile;
    QList <QString> stack;
    bool isCleaning;
    int row;
    int col;
    int max_rows;
    int max_cols;

private slots:
    void dirDoubleClicked(QString);
    void on_toolButton_2_clicked();
};

#endif // MAINWINDOW_H
