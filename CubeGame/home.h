#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QPixmap>
#include <QPalette>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLCDNumber>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QMessageBox>
#include "piecebox.h"

class Home : public QWidget
{
    Q_OBJECT

public:
    Home(QWidget *parent = 0);
    ~Home();
    void initGrapicsView();
public slots:
    void slot_startgame();
    void slot_pausegame();
    void slot_endgame();
    void slot_restartgame();
    void slot_moveBox();
    void slot_update_score(int);
    void slot_gameOver();
private:
    QPixmap m_pixmap;
    QPalette m_palette;
    QHBoxLayout *mainLayout;
    QHBoxLayout *panel;
    QPushButton *startBtn;
    QPushButton *pauseBtn;
    QPushButton *reStartBtn;
    QPushButton *endBtn;
    QLCDNumber *scoreLcd;
    QGraphicsView *view;
    QGraphicsScene *m_scene;
    QGraphicsLineItem *m_topLine;
    QGraphicsLineItem *m_bottomLine;
    QGraphicsLineItem *m_leftLine;
    QGraphicsLineItem *m_rightLine;

    PieceBox *m_currentBox;
    PieceBox *m_nextBox;

    QList<int> m_rowList;
    int score = 0;
    bool pause_status = false;
public slots:
    void slot_clearFullRows();
};

#endif // HOME_H
