#ifndef CHART_H
#define CHART_H

#include <QObject>
#include <QTimer>

class Chart : public QObject
{
    Q_OBJECT
public:
    explicit Chart(QObject *parent = 0);
    QTimer *m_timer;

signals:

public slots:
    void handleTimeOut();
};

#endif // CHART_H
