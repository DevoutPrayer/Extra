#include "commointer.h"
#include<QDebug>

ComMointer::ComMointer()
{
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_timeout()));
    timer->start(1000);
}

void ComMointer::slot_timeout()
{
    //qDebug()<<"xxxx";
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        bool flag = false;
        for(int i = 0; i < com_avaliable.count();i++)
        {
            if(com_avaliable.at(i).serialPortInfo.portName() == info.portName())
            {
                SerialPortInfo serialPortInfo;
                serialPortInfo.isCheck = true;
                serialPortInfo.serialPortInfo = com_avaliable.at(i).serialPortInfo;
                com_avaliable.removeAt(i);
                com_avaliable.insert(i,serialPortInfo);
                flag = true;
            }
        }
        /*foreach (SerialPortInfo serialPortInfo, com_avaliable)
        {
            if(serialPortInfo.serialPortInfo.portName()==info.portName())
            {
                serialPortInfo.isCheck = true;
                flag = true;
            }
        }*/
        //qDebug()<<"111-"<<flag;
        if(!flag)
        {
           SerialPortInfo serialPortInfo;
           serialPortInfo.serialPortInfo = info;
           serialPortInfo.isCheck = true;
           com_avaliable.append(serialPortInfo);
           qDebug() << "Name : " << info.portName();
           qDebug() << "Description : " << info.description();
           qDebug() << "Manufacturer: " << info.manufacturer();
           qDebug() << "Serial Number: " << info.serialNumber();
           qDebug() << "System Location: " << info.systemLocation();
           emit signal_com_conn(info.portName(),info.description());
        }
    }
    for(int i = 0;i < com_avaliable.count();i++)
    {
        if(com_avaliable.at(i).isCheck == false)
        {
            com_avaliable.removeAt(i);
            qDebug()<<tr("USB断开连接。");
        }
    }
    for(int i = 0;i < com_avaliable.count();i++)
    {
        SerialPortInfo serialPortInfo;
        serialPortInfo.isCheck = false;
        serialPortInfo.serialPortInfo = com_avaliable.at(i).serialPortInfo;
        com_avaliable.removeAt(i);
        com_avaliable.insert(i,serialPortInfo);

    }
    qDebug()<<com_avaliable.count();
}
