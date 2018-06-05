#include "screenlabel.h"

ScreenLabel::ScreenLabel(QWidget * parent):QLabel(parent)
{
   setStyleSheet("border:1px solid #0ff");
   setFixedSize(300,200);
}


void ScreenLabel::paintEvent(QPaintEvent *paintEvent)
{

}
