#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("paintWidget"));
}

PaintWidget::~PaintWidget()
{

}
void PaintWidget::paintEvent(QPaintEvent *event)
{
        QPainter painter(this);
        painter.drawLine(80, 100, 650, 500);
        painter.setPen(Qt::red);
        painter.drawRect(10, 10, 100, 400);
        painter.setPen(QPen(Qt::green, 5));
        painter.setBrush(Qt::blue);
        painter.drawEllipse(50, 150, 400, 200);
}
