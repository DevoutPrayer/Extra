#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);
    void slotClose();
signals:
    void signalShow();
public slots:

private:
    QGridLayout *mainLayout;
    QPushButton *closePushBtn;
};

#endif // MYWIDGET_H
