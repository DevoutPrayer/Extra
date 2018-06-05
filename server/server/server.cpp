#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <pthread.h>
#include <arpa/inet.h>//inet_ntop()
#include <unistd.h>
#include <time.h>
#include <QTextCodec>//用汉字编码
#include <QString>
#include <QDebug>
#include "fd_vector.h"
#define BUF_SZIE 1024

//先创建一个顺序表 *全局变量
Fd_Vector *Client_fd_list;

//全局变量 记录上一个发送者的fd
//如果上次的落子的fd是这次发送者的fd 就不做处理
int TheLastfd = 1024;

//服务器写回客户端的函数[对一个客户端写回]，减少7处重复
void write_copy_message(int fd,const char *msg,int len){
    if(write(fd,msg,len) != len){
        fprintf(stderr,"write_copy_message :%s\n",strerror(errno));
        exit(1);
    }
    }
//服务器协会客户端数据的函数[对所有的客户端写回]，取消3处的重复
void writes_copy_message(const char* msg,int len){
    for(int i = 0;i < Client_fd_list->count;i++){
        if(write(Client_fd_list->fds[i],msg,len) != len){
           fprintf(stderr,"writes_copy_message :%s\n",strerror(errno));
        }
    }

}

//在虚拟的棋盘buf中保存棋子的位置，  判断是否达到一方赢了
int   savePos(int a,int fd)
{
    //保存自己的棋子位置
    //虚拟的棋盘
    static int buf[30][30] = {{0}};
        int i;
        i= a/30;
        int j;
        j= a%30;
        buf[i][j]=fd;
        //判断棋盘

        //水平方向遍历
        int x,y;
        int count = 1;
        //向右找
        for(y = j+1;y<j+5 && y<=29;y++){
            if(buf[i][y] == fd){
                count++;
            }else{
                break;
           }
        }

        //向左找
        for(y = j-1;y>j-5 && y>=0;y--){

            if(buf[i][y] == fd){
                count++;
            }else{
                break;
            }
        }
        if(count == 5)
        {
           memset(buf,0,sizeof(int)*900);
        return 1;
    }
        //count 清零
        count = 1;
        //竖直方向
        //向下找
        for(x = i+1;x<i+5 && x<=29;x++){
            if(buf[x][j] == fd){
                count++;
            }else{
                break;
            }
        }
        //向上找
        for(x = i-1;x>i-5 && x>=0;x--){
            if(buf[x][j] == fd){
                count++;
            }else{
                break;
            }

        }
        if(count == 5){
            memset(buf,0,sizeof(int)*900);
            return 1;
        }
        count = 1;

        //斜向右下
        for(x=i+1,y=j+1;x<i+5&&x<=29&&y<=29;x++,y++)
            {
            if(buf[x][y]==fd)
                {
                count++;
            }else{
                break;
            }
        }
        //斜向左上
        for(x=i-1,y=j-1;x>i-5&&x>=0&&y>=0;y--,x--)
            {
            if(buf[x][y]==fd)
                {
                count ++;
            }else{
                break;
            }
        }
        if(count == 5){
            memset(buf,0,sizeof(int)*900);
            return 1;
        }
        //斜向右上
        for(x=i-1,y=j+1;y<j+5&&y<=29&&x>=0;x--,y++)
            {
            if(buf[x][y]==fd)
                {
                count ++;
            }else{
                break;
            }
        }
        //斜向左下
        for(x=i+1,y=j-1;x<i+5&&x<=29&&y>=0;x++,y--)
            {
            if(buf[x][y]==fd)
                {
                count ++;
            }else{
                break;
            }
        }
        if(count == 5){
            memset(buf,0,sizeof(int)*900);
            return 1;
        }
        return 0;
}


//线程
void * do_servers(void* arg){
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //客户端的fd
    int clientfd = (int)arg;
    /**获取对方的IP地址：或有或无， 或者获取对方的昵称，可扩展*/
    struct sockaddr_in addr;
    int len = sizeof(addr);
    memset(&addr,0,len);
    //getpeername 获取客户端的IP
    if(getpeername(clientfd,(struct sockaddr*)&addr,(socklen_t *)&len) < 0){
        fprintf(stderr,"GetPeername %s\b",strerror(errno));
        pthread_exit((void *)-1);
    }
    char ip[16]={0};
    inet_ntop(AF_INET,&addr.sin_addr.s_addr,ip,16);
    //读取客户端发上来的信息
    char buffer[BUF_SZIE]={0};
    while(1){
        memset(buffer,0,sizeof(buffer));
        int nread = read(clientfd,buffer,BUF_SZIE);
        if(nread < 0){
            //意外出错
            fprintf(stderr,"read from clientfd %s\n",strerror(errno));
            pthread_exit((void *)-1);
        }else if(nread == 0){
            //客户端关闭了
            printf("%s client closed!\n",ip);
            //删除顺序表中的这个客户端的套节字描述符
            delete_fd_v(Client_fd_list,clientfd);
            pthread_exit((void *)-1);
        }else{
            //读到了这个客户端发送的信息
            //分析拿到的数据

            if(strstr(buffer,"#Command:") != NULL){
                //命令消息
                //服务器要发消息给除了拥有该线程以外的客户端一个窗口消息MessageBox
                //发给下一个客户端
                int myfd_index = get_fd_index(Client_fd_list,clientfd);
                char inviteMsg[256] = {0};
                if(myfd_index+1 != Client_fd_list->count){
                    //发给它的下家消息     
                    sprintf(inviteMsg,"#Invite:%d,%d",clientfd,Client_fd_list->fds[myfd_index+1]);
                    int len = strlen(inviteMsg);
                    write_copy_message(Client_fd_list->fds[myfd_index+1],inviteMsg,len);
                }else{
                    //发给它上家的消息
                    sprintf(inviteMsg,"#Invite:%d,%d",clientfd,Client_fd_list->fds[myfd_index-1]);
                    int len = strlen(inviteMsg);
                    write_copy_message(Client_fd_list->fds[myfd_index-1],inviteMsg,len);
                }
            } else if(strstr(buffer,"#Chat:") != NULL){
                //聊天信息
                /*可以扩展给发送的消息加上时间*/
                /*获取对方发送消息的时间*/
                time_t curtime = time(NULL);
                char timeBuf[128]={0};
                sprintf(timeBuf,"[%2d:%.2d:%.2d]",localtime(&curtime)->tm_hour,localtime(&curtime)->tm_min,localtime(&curtime)->tm_sec);

                //用一个循环给所有的客户端发送消息
                //把字符串的前6个字符去掉
                QString message(buffer);
                message.remove(0,6);
                for(int i = 0;i < Client_fd_list->count;i++){

                    if(Client_fd_list->fds[i] == clientfd){
                       char refined_messageme[BUF_SZIE];
                       sprintf(refined_messageme,"<a style='color:#C71585'>%s我:%s</a>",timeBuf,message.toStdString().c_str());
                       int len = strlen(refined_messageme);
                       write_copy_message(Client_fd_list->fds[i],refined_messageme,len);
                    }else{
                        char refined_messageotr[BUF_SZIE];
                        sprintf(refined_messageotr,"%s:%s",timeBuf,message.toStdString().c_str());
                        int len = strlen(refined_messageotr);
                        write_copy_message(Client_fd_list->fds[i],refined_messageotr,len);
                    }

                }//给所有的客户端消息发送完毕
            }else if(strstr(buffer,"#disAgree:") != NULL){
                //给被拒绝的玩家发送消息
                QString disAgreeMsg(buffer);
                disAgreeMsg.remove(0,10);
                //获取到被拒绝玩家的fd
                char disAgree[10] = "#disAgree";
                write_copy_message(disAgreeMsg.toInt(),disAgree,9);


            }else if(strstr(buffer,"#Agree:") != NULL){
                //发送玩家同意的消息给邀请者+fd
                QString agree(buffer);
                QString other(buffer);
                agree.remove(0,7);
                for(int i = 0;i < Client_fd_list->count;i++){
                    if(Client_fd_list->fds[i] == agree.toInt()){
                        write_copy_message(Client_fd_list->fds[i],buffer,nread);
                    }else{
                        //给其他人发送开始消息
                        other.remove(7,1);
                        write_copy_message(Client_fd_list->fds[i],other.toStdString().c_str(),7);
                    }
                }
            }else if(strstr(buffer,"#Pos:") != NULL){
                QString temp(buffer);
                QString x("#");
                int index = temp.indexOf(x);
                temp.remove(index,strlen(buffer));
                qDebug()<<"pos buffer:"<<buffer;
                int currentSenderFd  = temp.toInt();
                //拿到了目前发送消息者的fd
                //如果上一次的fd 和本次发送消息的fd是同一个，则不做转发处理
                if(currentSenderFd != TheLastfd){
                    //本次和上次的fd不是同一个则保存
                    TheLastfd = currentSenderFd;
                    //把"?#Pos:?" 复原为 "#Pos:?"
                    QString pos(buffer);
                    QString z("#");
                    int indexof = pos.indexOf(z);
                    pos.remove(0,indexof);
                    writes_copy_message(pos.toStdString().c_str(),nread);

                    if(currentSenderFd == clientfd){
                        QString positon(pos);
                        positon.remove(0,5);
                        if(1 == savePos(positon.toInt(),clientfd)){
                            //向赢家和其他人发送信号
                            char winbuf[15]={0};
                            sprintf(winbuf,"%d#Winner:",clientfd);
                            int winnerlen = strlen(winbuf);
                            writes_copy_message(winbuf,winnerlen);
                        }
                    }
                }
            }else{
                writes_copy_message(buffer,nread);
            }
        }
    }//while(1) finished

    return ((void*)0);
}


int main(void){

    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        fprintf(stderr,"socket %s \n",strerror(errno));
        exit(1);
        }

    //填写主机信息
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);/**port ****** is ****** here **/
    addr.sin_addr.s_addr = INADDR_ANY;

    //设置端口可重用
    int on =1;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

    //绑定主机套节字
    if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr)) < 0){
        fprintf(stderr,"bind is:%s\n",strerror(errno));
        exit(1);
    }

    //监听
    if(listen(sockfd,50) < 0){
        fprintf(stderr,"listen is %s\n",strerror(errno));
        exit(1);
    }
    //接受链接

    Client_fd_list = create_fd_v();
    while(1){
        //接受得到客户端的套节字，然后把套节字放到顺序表中
        int clientfd = accept(sockfd,NULL,NULL);
        //服务器需要接受每一个主机发送给它的信息，并把接受到的信息发送给所有连上来的客户端
        //接受和发送是异步处理的，每一个客户端连上来的时候建立一个线程收信息,
        //并把客户端的套节字描述符存放到顺序表中
        //服务器还要给所有的客户端发送接受到的信息
        qDebug()<<"new clientcoming clientfd:"<<clientfd<<endl;
        //1.把该客户端的描述符加到顺序表中
        add_fs_v(Client_fd_list,clientfd);
        //2.建立线程来接受该客户端发上来的信息，并把信息转发给所有的（包括自己）的客户端
        /*建立线程去做这些事情 设置分离属性？*/
        pthread_t th;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
        /*传入客户端套节字描述符*/
        pthread_create(&th,&attr,do_servers,(void *)clientfd);
    }
}

