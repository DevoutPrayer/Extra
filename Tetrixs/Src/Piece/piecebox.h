#ifndef PIECEBOX_H
#define PIECEBOX_H

/********
 * 方块组
 * 4*4
 *
 *
 * ******/

#include <QGraphicsItemGroup>
#include <QKeyEvent>
#include <QTimer>
#include "enumHeader.h"
#include <QTransform>
#include "onepiece.h"
#include <QGraphicsItem>

class pieceBox :public QObject,public QGraphicsItemGroup
{
    Q_OBJECT
public:
    pieceBox();
    //颜色表
    static QColor colorTable[7];
    //绘制方块组的边框矩形
    virtual QRectF boundingRect() const;
    //是否发生碰撞
    bool isCollding() const;
    //获取当前的方块类型
    BoxType getCurrentBoxType() const;
    //创建方块组
    void createBox(const QPointF &point = QPointF(0,0),
                   BoxType currentBoxType = RandomShape);
    //消除方块组
    void clearBoxGroup(const bool &isClear = false);

protected:
    virtual void keyPressEvent(QKeyEvent * event);

signals:
    void signal_needNewBox();
    void signal_gameOver();
public slots:
    void slot_moveOneStep();
    void slot_startTimer(int timeSec);
    void slot_stopTimer();
private:
    QTimer *m_Timer;
    BoxType m_currentBoxType;
    QTransform m_oldTransform;
    QList<onePiece *> m_pieceBoxList;   //存放新方块组的四个方块
};

#endif // PIECEBOX_H
