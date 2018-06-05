#include "mylabel.h"
#include <QDebug>
MyLabel::MyLabel(QWidget *parent) :
    QLabel(parent),flag(0)
{
    map1.load(":/mark.jpg");
    map2.load(":/andy.jpg");
}

void MyLabel::paintEvent(QPaintEvent *){
    QPainter painter(this);//指定父控件

    qDebug()<<"in Mylabel paintEvent!";
    //将Map铺满整个组建
    if(flag == 0){
    painter.drawPixmap(0,0,this->width(),this->height(),map1);
    }else{
    painter.drawPixmap(0,0,this->width(),this->height(),map2);
    }

}
