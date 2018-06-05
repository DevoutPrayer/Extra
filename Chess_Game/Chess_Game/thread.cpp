#include "thread.h"
#include <QDebug>
#define BUF_SIZE 1024

Thread::Thread()
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
}

//客户端链接到服务器上面并返回一个int 的socketfd
int Thread::conn_to_server(){
    int client_socked_fd = socket(AF_INET,SOCK_STREAM,0);
    if(client_socked_fd < 0){

        fprintf(stderr,"client_socked_fd %s\n",strerror(errno));
        exit(1);
    }
    //填写主机的信息
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);/********************port *********************/
    inet_pton(client_socked_fd,"172.16.3.143",&addr.sin_addr.s_addr);

    //connect
    if(::connect(client_socked_fd,(struct sockaddr*)&addr,sizeof(addr)) < 0){
        fprintf(stderr,"client_socked_fd %s\n",strerror(errno));
        exit(1);
    }
    return client_socked_fd;
}


void Thread::run(){
    /*客户端：1发送聊天信息，2实时接受聊天信息
     客户端需要分离出来一个子线程，专门用来读取数据，
     客户端需要：读取服务器发送到的数据，可以以信号的形式将数据发送给主线程，然后由主线程对相关的组建作出修改！*/
    //建立网络链接，拿到套节字描述符
    sockfd = conn_to_server();
    qDebug()<<"socketfd:"<<sockfd;

    //接受服务器返回来的数据，并以信号的形式发给主线程，实现相关的功能
    int nread;
    char buffer[BUF_SIZE];
    while(1){
        memset(buffer,0,sizeof(buffer));

        nread = read(sockfd,buffer,sizeof(buffer));
        if(nread < 0){
        //error
           fprintf(stderr,"client read from server:%s\b",strerror(errno));
           sleep(1);
           exit(1);
        }else if(nread == 0){
            printf("server connection closed!\n");
            exit(1);

        }else{
            //读到了服务器发送回来的数据，
            //分析

            if(strstr(buffer,"#Agree") != NULL){
                //对方同意了我的请求

                if(strlen(buffer) >= 8){
                    QString agreeBuf(buffer);
                    int myfd = agreeBuf.remove(0,7).toInt();
                    qDebug()<<"received myfd:"<<myfd;
                    emit agree_ToStrat_Game(myfd);
                }else{
                    emit agree_ToStrat_Game(2);
                }

            }else if(strstr(buffer,"#Invite:") != NULL){
                //服务器发给了我开始命令  "#Invite:%d,%d"
                //第一个是对方的fd，第二个是自己的
                QString temp(buffer);
                temp.remove(0,8);//?,?
                QString teammatefd(temp);
                teammatefd.remove(1,2);
                QString myfd(temp);
                myfd.remove(0,2);
                //得到对方和自己的fd
                emit thread_gameStart_Invite(teammatefd.toInt(),myfd.toInt());

            }else if(strstr(buffer,"#disAgree") != NULL){
                //收到了拒绝的消息
                emit thread_gameDisagree();
                qDebug()<<"对方拒绝与我玩游戏";

           }else if(strstr(buffer,"#Pos:") != NULL){
            //收到了坐标信息解析为int型
               QString positon(buffer);
               positon.remove(0,5);
               emit thread_position(positon.toInt());
               //qDebug()<<"收到坐标 x:"<<positon.toInt()/30<<"y:"<<positon.toInt()%30;

           }else if(strstr(buffer,"#Winner") != NULL){
               //服务器发回了赢家的消息
               QString winner(buffer);
               QString x("#");
               int index = winner.indexOf(x);
               winner.remove(index,strlen(winner.toStdString().c_str()));
               qDebug()<< "winner is:"<<winner.toInt();
               emit thread_winner(winner.toInt());

           }else{
                //服务器发给我的是聊天信息
                emit thread_copy_message(buffer);
            }
        }
    }
}
