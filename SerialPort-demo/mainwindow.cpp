#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialPort = new SerialPort;
    comMointer = new ComMointer;
    connect(comMointer,SIGNAL(signal_com_conn(QString,QString)),this,SLOT(slot_com_conn(QString,QString)));
    connect(ui->sendBtn,SIGNAL(clicked(bool)),this,SLOT(slot_send_msg()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_com_conn(QString portname, QString description)
{
    qDebug()<<"PortName="<<portname<<";description="<<description;
    serialPort->openPort(portname);
}

void MainWindow::slot_send_msg()
{
    serialPort->writeMsg(QString("1"));
}
