#ifndef WIDGET_H
#define WIDGET_H
#include <QtGui/QWidget>
#include <QTextBrowser>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPaintEvent>
#include <QImage>
#include <QPainter>
#include <QMessageBox>
#include <QTimerEvent>
#include <QTimer>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "chessindividual.h"
#include "mylabel.h"
#include "thread.h"

#include "QDebug"

class MyTextEdit;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    //void paintEvent(QPaintEvent *);
    Thread *th;//添加线程成员
private:
    QTextBrowser *chatBrowser;
    MyTextEdit *messageSend;
    QListWidget *chessNumber;
    QPushButton *startBtn;
    QLabel *timeLabel;
    QLabel *playerLable;
    MyLabel *imageLabel;
    //右边的棋盘部分
    ChessIndividual *chessArea;
    //计时器
    QTimer *timer;
    //时间
    int sec;
    int min;
    //黑白子的标记
    int flag;
    //自己在服务器上的fd
    int myfdOnServer;
    //闪烁的flag
    int blinkflag;
    //上次落子的位置
    int lastTimePos;
    //timer的id
    int timerID;
    //闪烁 是否为第一个落子的标志
    int count;
    //如果发送了#Agree信号的必然是玩家
    //如果发送了#command 信号，并且收到#Agree信号的必然是玩家;
    //如果发送了#command 信号又收到了#disAgree信号必然不是玩家
protected:
    void timerEvent(QTimerEvent *);
public slots:
    //聊天框的处理：向服务器发送聊天信息
    void sendMsgToServer(QString);
    //start按钮的处理：向服务器发送信息#Command:
    void sendStartMsgToServer();
    //接受到了开始的邀请命令，开启对话框
    void JoinOrNot(int,int);
    //接收到了拒绝游戏的命令
    void refuse();
    //刷新计时器
    void flushTime();
    //开始游戏
    void startGame(int);
    //向服务器发送坐标信息
    void sendMyposition(int);
    //收到坐标信号在相应的位置画图
    void getPos_and_paintImg(int);
    //收到赢家的fd
    void getWinnerInfo(int);

};
class MyTextEdit: public QTextEdit{
    Q_OBJECT//信号和槽的类都是必须的宏名
public:
    MyTextEdit(QWidget *parent = 0);
protected:
    //重写键盘处理函数
    void keyPressEvent(QKeyEvent *e);
signals:
    void sendChatMsg(QString);
//public slots:


};
#endif // WIDGET_H
