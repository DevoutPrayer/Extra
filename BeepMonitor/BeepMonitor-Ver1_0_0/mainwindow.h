#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChartView>
#include <QTimer>
#include <QTime>
#include <QChart>
#include <QValueAxis>
#include <QSplineSeries>
#include <QLineSeries>
#include <QtCharts/QCategoryAxis>
#include "threaddisplay.h"
using namespace QtCharts;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void handleTimeOut();

private:
    Ui::MainWindow *ui;
    QChart *m_chart;
    QTimer *m_timer;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    QLineSeries *m_lineSeries1;
    QLineSeries *m_lineSeries2;
    QSplineSeries *m_splineSeries;
    QList<QPoint> lineSeries1List;
    QList<QPoint> lineSeries2List;
    ThreadDisplay threadDisplay;

};

#endif // MAINWINDOW_H
