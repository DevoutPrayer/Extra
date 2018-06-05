#include "piecebox.h"
#include "enumHeader.h"
#include <QList>
#include <QDebug>

QColor pieceBox::colorTable[7] = {QColor(200,0,0,100),QColor(255,200,0,100),
                                 QColor(0,0,200,100),QColor(0,200,0,100),
                                 QColor(0,200,255,100),QColor(200,0,255,100),
                                 QColor(150,100,100,100)};

pieceBox::pieceBox()
{
    m_pieceBoxList.clear();
    //使得方块组支持键盘操作
    setFlags(QGraphicsItem::ItemIsFocusable);
    //保存矩阵的原状态，使得可以还原矩阵
    m_oldTransform = transform();
    m_Timer = new QTimer(this);
    connect(m_Timer,SIGNAL(timeout()),this,SLOT(slot_moveOneStep()));
    m_currentBoxType = RandomShape;
}

//绘制方块组的边框矩形
QRectF pieceBox::boundingRect() const
{
    qreal penWidth = PEN_WIDTH;
    return QRectF(-(PIECE_DIAMETER*2 - penWidth) / 2, -(PIECE_DIAMETER*2 - penWidth) / 2,
                  PIECE_DIAMETER*4-penWidth, PIECE_DIAMETER*4-penWidth);
}

bool pieceBox::isCollding() const
{
    //依次检测方块组中的每个方块的碰撞
    foreach (onePiece *piece, m_pieceBoxList) {
//        qDebug() << "colliding number:" << piece->collidingItems().count();
        //获取与该方块碰撞的方块的个数
        if(piece->collidingItems().count() > 1)
        {
            return true;
        }
    }
    return false;
}

BoxType pieceBox::getCurrentBoxType() const
{
    return m_currentBoxType;
}

void pieceBox::createBox(const QPointF &point, BoxType currentBoxType)
{
    int boxType = currentBoxType;
    if(boxType == RandomShape)
    {
        boxType = qrand() % 7;
    }
    //设置该方块组的颜色
    QColor boxColor = colorTable[boxType];
    //准备四个小方块

    //恢复方块组的变换矩阵，因为之前的方块组的变换会导致变换矩阵的位置发生变换,
    //防止新的方块组因为旧的方块组变换异常
    setTransform(m_oldTransform);
    setRotation(0);
    resetTransform();

    m_pieceBoxList.clear();
    for(int i = 0;i < 4;i++)
    {
        onePiece *piece = new onePiece(boxColor);
        m_pieceBoxList.append(piece);
        //将小方块添加到方块组中
        addToGroup(piece);
    }
    //设置方块组的形状
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
    //设置方块组的位置
    setPos(point);
    //检测是否发生碰撞,发生碰撞，游戏结束
    if(isCollding())
    {
        slot_stopTimer();
        emit signal_gameOver();
    }
}

//删除方块组中的小方块到情景中
void pieceBox::clearBoxGroup(const bool &isClear)
{
    QList<QGraphicsItem *> itemList = childItems();
    foreach (QGraphicsItem *piece, itemList) {
        removeFromGroup(piece);
//        qDebug() << "clear box group" << isClear;
        if(isClear)
        {
            //销毁小方块
           ((onePiece *)piece)->deleteLater();
        }
    }
    m_pieceBoxList.clear();
}

void pieceBox::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Down:
        moveBy(0,20);
        //检测是否碰撞
        if(isCollding())
        {
           moveBy(0,-20);
           clearBoxGroup();
           //需要新的方块
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
    case Qt::Key_Space: //快速下落
        moveBy(0,20);
        while (!isCollding()) {
            moveBy(0,20);
        }
        moveBy(0,-20);
        clearBoxGroup();
        //需要新的方块
        emit signal_needNewBox();
        break;
    default:
        break;
    }
}

void pieceBox::slot_moveOneStep()
{
    moveBy(0,20);
//    qDebug() << "move one step";
    if(isCollding())
    {
        moveBy(0,-20);
        // 将小方块从方块组中移除到场景中
        clearBoxGroup();
        //需要新的方块
        emit signal_needNewBox();
    }
}

void pieceBox::slot_startTimer(int timeSec)
{
    m_Timer->start(timeSec);
}

void pieceBox::slot_stopTimer()
{
    m_Timer->stop();
}
