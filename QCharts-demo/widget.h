#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QSplineSeries>
#include <QLineSeries>
#include <QTimer>
#include <QTime>
QT_CHARTS_USE_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QGridLayout *mainLayout;
    QChart *m_chart;
    QChartView *m_chartView;
    QValueAxis *m_axis;
    //QSplineSeries *m_splineSeries;
    QLineSeries *m_splineSeries;
    QTimer *m_timer;
    int width = 20;
    int margin = 2;
    int left = 0;
private slots:
    void handleTimeOut();
};

#endif // WIDGET_H
