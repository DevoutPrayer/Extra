#ifndef THREADDISPLAY_H
#define THREADDISPLAY_H

#include <QThread>
#include <QtCharts/QChartView>
#include "chart.h"

using namespace QtCharts;
class ThreadDisplay : public QThread
{
public:
    ThreadDisplay(QChartView *);
    void run();
private:
    Chart *m_chart;
    QChartView *m_chartView;
};

#endif // THREADDISPLAY_H
