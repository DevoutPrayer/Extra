#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "clientwindow.h"

#include "server_window.h"


#define SPACE 60
struct pieces
{
    QPoint pos;
    bool belongTo;
};
enum ChessColor{
    black,
    white
};
enum ChessType{
    NoChess,
    BlackChess,
    WhiteChess
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void isAnyOneSuccess();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
private:
    QPoint cursorPos;
    bool isOnFocus;
    QVector<pieces> piece;
    bool turn;
    bool isAbleGo = false;
    char chessPanel[15][15];
    QAction *clientAction;
    QAction *serverAction;
    bool isServer = false;
    bool isClient = false;
signals:
    void signal_chessGo(int x,int y);
    void chessWin(ChessType);
public slots:
    void slot_peerChessGo(int x,int y);
    void slot_canGo();
private slots:
    void slot_openServer();
    void slot_openClient();
    void slot_ServerClose();
    void slot_ClientClose();
    void slot_chessWin(ChessType);
};
/*通过重载paintEvent huipaintEvent*/
#endif // MAINWINDOW_H
