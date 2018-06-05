#ifndef DEVOUTPRAYER_TIMER_H
#define DEVOUTPRAYER_TIMER_H
#include <QTimer>
#include <QTime>
#include <QString>



class DevoutPrayer_Timer : public QObject
{
    Q_OBJECT
public:
    DevoutPrayer_Timer();
    QString get_current_time();
private:
    QTimer *timer;
private slots:
    void slot_get_current_time();
signals:
    void signal_current_time(QString);
};

#endif // DEVOUTPRAYER_TIMER_H
