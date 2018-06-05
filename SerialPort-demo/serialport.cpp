#include "serialport.h"
#include <qDebug>

SerialPort::SerialPort()
{
    /*qDebug()<<tr("程序进行");
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "Serial Number: " << info.serialNumber();
        qDebug() << "System Location: " << info.systemLocation();
    }*/
    this->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);
    this->setDataBits(QSerialPort::Data8);
    this->setFlowControl(QSerialPort::NoFlowControl);
    this->setStopBits(QSerialPort::OneStop);
    this->setParity(QSerialPort::NoParity);
    connect(this,SIGNAL(readyRead()),this,SLOT(slot_DataRec()));
}

bool SerialPort::openPort(QString port)
{
    this->setPortName(port);
    this->close();
    if(this->open(QIODevice::ReadWrite))
        return true;
    else
        return false;

}

void SerialPort::slot_DataRec()
{
    QByteArray temp = this->read(1);
    qDebug()<<temp;
}

void SerialPort::writeMsg(QString msg)
{
    this->write(msg.toLatin1());
}
