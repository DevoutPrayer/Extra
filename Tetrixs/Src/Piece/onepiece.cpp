#include "onepiece.h"
#include <QPainter>
#include "enumHeader.h"

/****
 * 为了避免同一个方块组内小方块发生碰撞，
 * 小方块的大小实际为19.5*19.5，但是小方块加上笔刷的宽度后为20*20
 * 这样看起来是四个小方块连在一起的
 * **/

onePiece::onePiece(const QColor &brushColor)
    :m_brushColor(brushColor)
{
}

QRectF onePiece::boundingRect() const
{
    qreal penWidth = PEN_WIDTH;
    return QRectF(-(PIECE_DIAMETER - penWidth)/2, -(PIECE_DIAMETER - penWidth)/2,
                  PIECE_DIAMETER - penWidth, PIECE_DIAMETER - penWidth);
}

void onePiece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //背景贴图
    painter->drawPixmap(-PIECE_DIAMETER/2,-PIECE_DIAMETER/2,PIECE_DIAMETER,PIECE_DIAMETER,QPixmap(":/piece/Image/piece/box.png"));
    painter->setBrush(m_brushColor);
    //将方块的边界的颜色进行透明化
    QColor penColor = m_brushColor;
    // 将颜色的透明度减小
    penColor.setAlpha(200);
    painter->setPen(penColor);
    //使用当前的笔刷和笔画矩形框
    painter->drawRect(-PIECE_DIAMETER/2, -PIECE_DIAMETER/2, PIECE_DIAMETER, PIECE_DIAMETER);
}

QPainterPath onePiece::shape() const
{
    QPainterPath path;
    //去除笔刷的宽度，这样同一个方块组的方块就不会被检测出碰撞的情况
    path.addRect(-(PIECE_DIAMETER-PEN_WIDTH)/2,-(PIECE_DIAMETER-PEN_WIDTH)/2,PIECE_DIAMETER-PEN_WIDTH,PIECE_DIAMETER-PEN_WIDTH);
    return path;
}
