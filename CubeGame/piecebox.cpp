#include "piecebox.h"

PieceBox::PieceBox()
{
    m_pieceBoxList.clear();
    setFlags(QGraphicsItem::ItemIsFocusable);
    m_oldTransform = transform();
    m_Timer = new QTimer(this);
    connect(m_Timer,SIGNAL(timeout()),this,SLOT(slot_moveOneStep()));
    m_currentBoxType = RandomShape;
}


QRectF PieceBox::boundingRect() const
{
    qreal penWidth = PEN_WIDTH;
    return QRectF(-(PIECE_SIDE_LENGTH*2 - penWidth) / 2, -(PIECE_SIDE_LENGTH*2 - penWidth) / 2,
                  PIECE_SIDE_LENGTH*4-penWidth, PIECE_SIDE_LENGTH*4-penWidth);
}
bool PieceBox::isCollding() const
{
    foreach (OnePiece *piece, m_pieceBoxList) {
        if(piece->collidingItems().count() > 1)
        {
            return true;
        }
    }
    return false;
}

void PieceBox::createBox(const QPointF &point, BoxType currentBoxType)
{
    int boxType = currentBoxType;
    if(boxType == RandomShape)
    {
        boxType = qrand() % 7;
    }
    QColor boxColor = colorTable[boxType];
    setTransform(m_oldTransform);
    setRotation(0);
    resetTransform();

    m_pieceBoxList.clear();
    for(int i = 0;i < 4;i++)
    {
        OnePiece *piece = new OnePiece(boxColor);
        m_pieceBoxList.append(piece);
        addToGroup(piece);
    }
    switch (boxType) {
    case IShape:
        m_currentBoxType = IShape;
        m_pieceBoxList.at(0)->setPos(-30,-10);
        m_pieceBoxList.at(1)->setPos(-10,-10);
        m_pieceBoxList.at(2)->setPos(10,-10);
        m_pieceBoxList.at(3)->setPos(30,-10);
        break;
    case JShape:
        m_currentBoxType = JShape;
        m_pieceBoxList.at(0)->setPos(10,-10);
        m_pieceBoxList.at(1)->setPos(10,10);
        m_pieceBoxList.at(2)->setPos(10,30);
        m_pieceBoxList.at(3)->setPos(-10,30);
        break;
    case LShape:
        m_currentBoxType = LShape;
        m_pieceBoxList.at(0)->setPos(-10,-10);
        m_pieceBoxList.at(1)->setPos(-10,10);
        m_pieceBoxList.at(2)->setPos(10,30);
        m_pieceBoxList.at(3)->setPos(-10,30);
        break;
    case OShape:
        m_currentBoxType = OShape;
         m_pieceBoxList.at(0)->setPos(-10,-10);
         m_pieceBoxList.at(1)->setPos(10,-10);
         m_pieceBoxList.at(2)->setPos(-10,10);
         m_pieceBoxList.at(3)->setPos(10,10);
        break;
    case SShape:
        m_currentBoxType = SShape;
         m_pieceBoxList.at(0)->setPos(30,-10);
         m_pieceBoxList.at(1)->setPos(10,-10);
         m_pieceBoxList.at(2)->setPos(10,10);
         m_pieceBoxList.at(3)->setPos(-10,10);
        break;
    case TShape:
        m_currentBoxType = TShape;
         m_pieceBoxList.at(0)->setPos(-10,-10);
         m_pieceBoxList.at(1)->setPos(10,-10);
         m_pieceBoxList.at(2)->setPos(30,-10);
         m_pieceBoxList.at(3)->setPos(10,10);
        break;
    case Zshape:
        m_currentBoxType = Zshape;
         m_pieceBoxList.at(0)->setPos(-10,-10);
         m_pieceBoxList.at(1)->setPos(10,-10);
         m_pieceBoxList.at(2)->setPos(10,10);
         m_pieceBoxList.at(3)->setPos(30,10);
        break;
    default:
        break;
    }
    setPos(point);
    if(isCollding())
    {
        slot_stopTimer();
        emit signal_gameOver();
    }
}
void PieceBox::clearBoxGroup(const bool &isClear)
{
    QList<QGraphicsItem *> itemList = childItems();
    foreach (QGraphicsItem *piece, itemList) {
        removeFromGroup(piece);
        if(isClear)
        {
           ((OnePiece *)piece)->deleteLater();
        }
    }
    m_pieceBoxList.clear();
}
void PieceBox::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Down:
        moveBy(0,20);
        if(isCollding())
        {
           moveBy(0,-20);
           clearBoxGroup();
           emit signal_needNewBox();
        }
        break;
    case Qt::Key_Left:
        moveBy(-20,0);
        if(isCollding())
        {
            moveBy(20,0);
        }
        break;
    case Qt::Key_Right:
        moveBy(20,0);
        if(isCollding())
        {
            moveBy(-20,0);
        }
        break;
    case Qt::Key_Up:
        setRotation(rotation()+90);
        if(isCollding())
        {
            setRotation(rotation()-90);
        }
        break;
    case Qt::Key_Space:
        moveBy(0,20);
        while (!isCollding()) {
            moveBy(0,20);
        }
        moveBy(0,-20);
        clearBoxGroup();
        emit signal_needNewBox();
        break;
    default:
        break;
    }
}
void PieceBox::slot_moveOneStep()
{
    moveBy(0,20);
    if(isCollding())
    {
        moveBy(0,-20);
        clearBoxGroup();
        emit signal_needNewBox();
    }
}
BoxType PieceBox::getCurrentBoxType() const
{
    return m_currentBoxType;
}
QColor PieceBox::colorTable[7] = {QColor(200,0,0,100),QColor(255,200,0,100),
                                 QColor(0,0,200,100),QColor(0,200,0,100),
                                 QColor(0,200,255,100),QColor(200,0,255,100),
                                 QColor(150,100,100,100)};
void PieceBox::slot_startTimer(int timeSec)
{
    m_Timer->start(timeSec);
}
void PieceBox::slot_stopTimer()
{
    m_Timer->stop();
}
