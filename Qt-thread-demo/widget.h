#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMutex>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QMutex mutex;
public slots:
    void slot_delete();
};

#endif // WIDGET_H
