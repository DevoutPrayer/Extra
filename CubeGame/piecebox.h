#ifndef PIECEBOX_H
#define PIECEBOX_H

#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QKeyEvent>
#include <QTimer>
#include <QTransform>

#include <QGraphicsBlurEffect>
#include <QPropertyAnimation>
#include "onepiece.h"

#define SPEED 500
enum BoxType
{
    IShape = 0,
    JShape,
    LShape,
    OShape,
    SShape,
    TShape,
    Zshape,
    RandomShape
};
class PieceBox : public QObject,public QGraphicsItemGroup
{
    Q_OBJECT
public:
    PieceBox();
    static QColor colorTable[7];
    virtual QRectF boundingRect() const;
    bool isCollding() const;
    BoxType getCurrentBoxType() const;
    void createBox(const QPointF &point = QPointF(0,0),
                   BoxType currentBoxType = RandomShape);
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
    QList<OnePiece *> m_pieceBoxList;
};

#endif // PIECEBOX_H
