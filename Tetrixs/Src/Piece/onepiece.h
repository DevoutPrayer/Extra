#ifndef ONEPIECE_H
#define ONEPIECE_H

/************
 *一块方块的绘制
 *
 *
 ***************/

#include <QGraphicsObject>
#include <QColor>

class onePiece : public QGraphicsObject
{
public:
    onePiece(const QColor &brushColor = Qt::red);
    //为项提供一个外围的边界矩形
    virtual QRectF boundingRect() const;
    //QGraphicsView调用，在本地坐标系统中绘制项
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    //重新定义项的形状，默认调用boundingRect获取项的矩形形状轮廓
    virtual QPainterPath shape() const;
private:
    QColor m_brushColor;

};

#endif // ONEPIECE_H
