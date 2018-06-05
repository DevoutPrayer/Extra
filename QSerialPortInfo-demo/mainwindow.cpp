#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<QSerialPortInfo> m_list = QSerialPortInfo::availablePorts();
    for(int i = 0;i<m_list.count();i++)
    {
        qDebug() << "Name : " << m_list.at(i).portName();
        qDebug() << "Description : " << m_list.at(i).description();
        qDebug() << "Manufacturer: " << m_list.at(i).manufacturer();
        qDebug() << "Serial Number: " << m_list.at(i).serialNumber();
        qDebug() << "System Location: " << m_list.at(i).systemLocation();
    }
    /*foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "Serial Number: " << info.serialNumber();
        qDebug() << "System Location: " << info.systemLocation();
    }*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
