#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialport.h"
#include "commointer.h"

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
    SerialPort *serialPort;
    ComMointer *comMointer;
private slots:
    void slot_com_conn(QString,QString);
    void slot_send_msg();
};

#endif // MAINWINDOW_H
