#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialPort : public QSerialPort
{
    Q_OBJECT
public:
    SerialPort();
    bool openPort(QString);
    void writeMsg(QString);
private slots:
    void slot_DataRec();
};

#endif // SERIALPORT_H
