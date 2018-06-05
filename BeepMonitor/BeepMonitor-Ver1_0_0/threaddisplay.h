#ifndef THREADDISPLAY_H
#define THREADDISPLAY_H

#include <QThread>
#include "chart.h"

class ThreadDisplay : public QThread
{
public:
    ThreadDisplay();
    void run();
private:
    Chart *m_chart;
};

#endif // THREADDISPLAY_H
