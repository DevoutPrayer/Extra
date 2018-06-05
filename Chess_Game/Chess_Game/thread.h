#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include<QTextCodec>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>//inet_ntop()
#include <unistd.h>



class Thread : public QThread
{
    Q_OBJECT
public:
    Thread();
    int sockfd;//套节字描述符
    //执行客户端连到服务器上的操作返回一个int的sockfd
    int conn_to_server();
//protected:
    void run();
signals:
    //发送接收到的信息信号给主线程
    void thread_copy_message(QString);
    //收到了其他玩家开始游戏的邀请
    void thread_gameStart_Invite(int,int);
    //接收到其他玩家同意加入游戏的消息
    //现在正式进入游戏
    void agree_ToStrat_Game(int);
    //接收到对方的拒绝信息
    void thread_gameDisagree();
    //接受到对方的坐标信息
    void thread_position(int);
    //接受到赢家的消息
    void thread_winner(int);

};

#endif // THREAD_H
