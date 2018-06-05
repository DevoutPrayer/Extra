#ifndef ONEPIECE_H
#define ONEPIECE_H

#include <QGraphicsObject>
#include <QColor>
#include <QPainter>

#define PIECE_SIDE_LENGTH 20
#define PEN_WIDTH         1

class OnePiece :public QGraphicsObject
{
public:
    OnePiece(const QColor &brushColor = Qt::red);
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    //QPainterPath shape() const;
private:
    QColor m_brushColor;
};

#endif // ONEPIECE_H
