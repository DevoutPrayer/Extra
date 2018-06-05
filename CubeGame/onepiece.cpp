#include "onepiece.h"

OnePiece::OnePiece(const QColor &brushColor):m_brushColor(brushColor)
{

}
void OnePiece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-PIECE_SIDE_LENGTH/2,-PIECE_SIDE_LENGTH/2,PIECE_SIDE_LENGTH,PIECE_SIDE_LENGTH,QPixmap(":/Imgs/box.png"));
    painter->setBrush(m_brushColor);
    QColor penColor = m_brushColor;
    penColor.setAlpha(200);
    painter->setPen(penColor);
    painter->drawRect(-PIECE_SIDE_LENGTH/2, -PIECE_SIDE_LENGTH/2, PIECE_SIDE_LENGTH, PIECE_SIDE_LENGTH);
}

QRectF OnePiece::boundingRect() const
{
    qreal penWidth = PEN_WIDTH;
    return QRectF(-(PIECE_SIDE_LENGTH - penWidth)/2, -(PIECE_SIDE_LENGTH - penWidth)/2,
                  PIECE_SIDE_LENGTH - penWidth, PIECE_SIDE_LENGTH - penWidth);
}

