#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "threaddisplay.h"

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
    //void handleTimeOut();

private:
    Ui::MainWindow *ui;

    //QList<QPoint> lineSeries1List;
    //QList<QPoint> lineSeries2List;
    ThreadDisplay *threadDisplay;

};

#endif // MAINWINDOW_H
