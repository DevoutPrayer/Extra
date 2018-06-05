#ifndef MYLABEL_H
#define MYLABEL_H
#include <QPaintEvent>
#include <QPainter>
#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);
    QPixmap map1,map2;

    int flag;//角色标记
signals:

public slots:
    private:

protected:
    void paintEvent(QPaintEvent *);

};

#endif // MYLABEL_H
