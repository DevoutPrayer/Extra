#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QPalette>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "piecebox.h"
#include "onepiece.h"
#include <QGraphicsLineItem>
#include <QMediaPlayer>

namespace Ui {
class Panel;
}

class Panel : public QWidget
{
    Q_OBJECT

public:
    explicit Panel(QWidget *parent = 0);
    ~Panel();
    void setbackground(const int &Lv);
    void initControlWidget();
    void initGraphicsViewWidget();

    /**游戏控制项***/
    void startGame();
    void pauseGame();
    void restartGame();
    void stopGame();

    void updateScore(const int fullRows = 0);

private slots:
    void on_pbt_startGame_clicked();

    void on_pbt_pauseGame_clicked();

    void on_pbt_restart_clicked();

    void on_pbt_stopGame_clicked();

    void slot_clearFullRows();

    void slot_gameOver();

    void slot_moveBox();
private:
    Ui::Panel *ui;
    QPalette m_Palette;
    QPixmap m_pixmap;
    int m_currentLv;
    int m_currentLVSpeed;
    bool m_isPauseGame;
    bool m_isGameOver;
    QGraphicsScene *m_scene;
    //四条边界线
    QGraphicsLineItem *m_topLine;
    QGraphicsLineItem *m_leftLine;
    QGraphicsLineItem *m_buttomLine;
    QGraphicsLineItem *m_rightLine;

    pieceBox *m_currentBox;
    pieceBox *m_nextBox;

    QList<int> m_rowList;
    QMediaPlayer *m_mediaPlayer;
};

#endif // PANEL_H
