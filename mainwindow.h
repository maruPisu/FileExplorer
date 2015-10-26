#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <file.h>
#include <QFileInfo>
#include <QDir>
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

private:
    Ui::MainWindow *ui;
    void insertFile(QFileInfo fileName, int, int, bool);
    void cleanUp();
    void clearLayout();
    void setGrid(int num);
    QWidget *spacer(int type);

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
    void on_back_button_clicked();
    void on_front_button_clicked();
};

#endif // MAINWINDOW_H
