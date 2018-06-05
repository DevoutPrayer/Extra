#ifndef COMMOINTER_H
#define COMMOINTER_H
#include <QSerialPortInfo>
#include <QTimer>
#include <QVector>

class ComMointer : public QObject
{
    Q_OBJECT
public:
    ComMointer();
private:
    struct SerialPortInfo
    {
        QSerialPortInfo serialPortInfo;
        bool isCheck;
    };
    QVector<SerialPortInfo> com_avaliable;
    QTimer *timer;
signals:
    void signal_com_conn(QString,QString);
private slots:
    void slot_timeout();
};

#endif // COMMOINTER_H
