#ifndef CHART_H
#define CHART_H

#include <QObject>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QTimer>
#include <QThread>
using namespace QtCharts;
class Chart : public QObject
{
    Q_OBJECT
public:
    explicit Chart(QChartView *chartView,QObject *parent = 0);
    QTimer *m_timer;

signals:

public slots:
    void handleTimeOut();
private:
    QChartView *m_chartView;
    QChart *m_chart;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    QLineSeries *m_lineSeries1;
    QLineSeries *m_lineSeries2;
    QSplineSeries *m_splineSeries;
    QList<QPoint> lineSeries1List;
    QList<QPoint> lineSeries2List;
};

#endif // CHART_H
