#include "devoutprayer_timer.h"

DevoutPrayer_Timer::DevoutPrayer_Timer()
{
    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(slot_get_current_time()));
    timer->start(1000);
}

QString DevoutPrayer_Timer::get_current_time()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    return text;
}

void DevoutPrayer_Timer::slot_get_current_time()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    emit signal_current_time(text);
}
