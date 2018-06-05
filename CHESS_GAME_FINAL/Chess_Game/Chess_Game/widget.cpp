#include "widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent),sec(0),min(0),flag(0),myfdOnServer(2),blinkflag(0),count(0)
{
    resize(800,600);
    //左半边所有组件
    chatBrowser = new QTextBrowser(this);
    chatBrowser->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    chatBrowser->setStyleSheet("background-image:url(:/guaniu.png);background-position:left bottom;background-attachment:fixed;background-repeat:none;color:#0000FF;font-size:12px;border-radius:3px;padding-bottom:5px;border:1px dashed #008000");
    messageSend =  new MyTextEdit(this);
    messageSend->setStyleSheet("color:#008000;border-radius:5px;border:3px solid #FFFFFF;font-size:14px;");
    messageSend->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    chessNumber =  new QListWidget(this);
    chessNumber->setStyleSheet("color:#FFD700;font-size:14px;font-weight:normal;");
    chessNumber->addItem("5 Chess");
    chessNumber->addItem("6 Chess");
    chessNumber->addItem("7 Chess");
    //chessNumber->currentRow();返回当前的列值几子棋？从0开始默认不选的是-1 点了start按钮把这个值传给服务器
    chessNumber->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    startBtn = new QPushButton("Start",this);
    startBtn->setFont(QFont("Monospace",18,QFont::Bold,false));
    startBtn->setStyleSheet("*:enabled{background-color:#FFA500;border-radius:6px;color:#F5F5F5;border:3px solid #FFA500;padding:5px 8px;} *:hover{background-color:#FFD700;border-radius:6px;color:#FFFFFF;border:3px solid #FFD700;padding:5px 8px;} *:!enabled{background-color:#A9A9A9;border-radius:6px;color:#FFFFFF;border:3px solid #A9A9A9;padding:5px 8px;}");
    startBtn->setCursor(Qt::PointingHandCursor);
    timeLabel = new  QLabel(this);
    timeLabel->setText("TIME: 00:00");
    timeLabel->setFont(QFont("Monospace",18,QFont::Bold,false));
    timeLabel->setStyleSheet("color:#FFD700;border:1px solid #FFFFFF;border-radius:6px;background-color:#FFFFFF");
    timeLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    playerLable = new QLabel(this);
    playerLable->setText("<B style='color:#A9A9A9;font-size:13px;white-space:pre;'>           Attention:</B><p style='color:#FFFF00;text-decoration:underline; text-indent:40px;'>who's turn</p>");
    playerLable->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    imageLabel = new MyLabel(this);
    imageLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);


    QHBoxLayout *list_stBtn = new QHBoxLayout;
    list_stBtn->addWidget(chessNumber,2);
    list_stBtn->addWidget(startBtn,1);

    QVBoxLayout *lefthalf = new QVBoxLayout;
    lefthalf->addWidget(chatBrowser,3);
    lefthalf->addWidget(messageSend,1);
    lefthalf->addLayout(list_stBtn,1);
    lefthalf->addWidget(timeLabel,1);
    lefthalf->addWidget(playerLable,1);
    lefthalf->addWidget(imageLabel,3);

    //右半边棋盘的类 900个封装成为一个类 初始化为Widget组件
    chessArea = new ChessIndividual(this);
    QHBoxLayout *mainlayout = new QHBoxLayout;
    mainlayout->addLayout(lefthalf,1);
    mainlayout->addWidget(chessArea,3);
    setLayout(mainlayout);
    //！@important 在widget类中可以直接使用chatBrowser的系统槽函数appaend(),不需要自己定义槽函数
    //messageSend和chatrowser是Widget类的私有成员，sendChatMsg()是MyTextEdit的定义的信号函数
    //connect(messageSend,SIGNAL(sendChatMsg(QString)),chatBrowser,SLOT(append(QString)));
    //客户端的发送消息的信号和槽函数(MyTextEdit KeyPressEvent)
    //Key_return pressed->SIGNAL sendMsgToServer ->write Thread::sockfd
    connect(messageSend,SIGNAL(sendChatMsg(QString)),this,SLOT
            (sendMsgToServer(QString)));


    th = new Thread;
    //客户端接收到的(read())从服务器发的【文字】消息，并把它追加到chatVrowser中
    connect(th,SIGNAL(thread_copy_message(QString)),chatBrowser,SLOT(append(QString)));
    //客户端收到从服务器发过来的开始游戏的邀请命令
    connect(th,SIGNAL(thread_gameStart_Invite(int,int)),this,SLOT(JoinOrNot(int,int)));
    //客户端收到对方发过来的同意游戏的消息 开始游戏
    connect(th,SIGNAL(agree_ToStrat_Game(int)),this,SLOT(startGame(int)));
    //客户端接收到对方发来的拒绝游戏的消息 弹出拒绝消息
    connect(th,SIGNAL(thread_gameDisagree()),this,SLOT(refuse()));
    //
    th->start();

    //开始按键的信号和槽函数
    connect(startBtn,SIGNAL(clicked()),this,SLOT(sendStartMsgToServer()));

    //计时器的初始化 一秒为最小计时单位
    timer = new QTimer(this);
    timer->setInterval(1000);
    //刷新时间 设置timelabel上面的时间
    connect(timer,SIGNAL(timeout()),this,SLOT(flushTime()));

    //900：1发送按键组坐标点的信号和槽函数，pos = i*30+j
   connect(chessArea->BtnGroup,SIGNAL(buttonPressed(int)),this,SLOT(sendMyposition(int)));

   //接受到位置的坐标信息并开始画图的信号函数和槽函数绑定
   connect(th,SIGNAL(thread_position(int)),this,SLOT(getPos_and_paintImg(int)));

   //接受到赢家的消息
   connect(th,SIGNAL(thread_winner(int)),this,SLOT(getWinnerInfo(int)));

}
//向服务器发送文字消息槽函数，meg来自与MyTextEdit的自定义信号
void Widget::sendMsgToServer(QString msg){
    //格式化输入，让服务器来判断发送的是聊天信息还是开始游戏的指令
    char message[1024] = {0};
    //发送的信息message
    sprintf(message,"#Chat:%s",msg.toStdString().c_str());
    ssize_t len = strlen(message);
    //qDebug()<<"message len :"<<len;
    if(write(th->sockfd,message,len)!=len){
        //发送失败
        fprintf(stderr,"snedtoserver %s\n",strerror(errno));
        exit(1);
    }
}
//开始按键的槽函数，向服务器发送命令
 void Widget::sendStartMsgToServer(){
    char StartMsg[10] = "#Command:";
    ssize_t len = strlen(StartMsg);
    if(write(th->sockfd,StartMsg,len) != len){
        fprintf(stderr,"send Start Command： %s",strerror(errno));
    }
 }

 //是不是开始游戏的槽函数，是否要开始都给对方发送消息
 void Widget::JoinOrNot(int parterfd,int myfd){


     char Content[256] = {0};
     sprintf(Content,"你同意与 玩家%d 玩一局不?",parterfd);
     int ret = QMessageBox::question(this,"有人邀请你加入游戏",Content,\
                           QMessageBox::No,QMessageBox::Yes);
     if(ret == QMessageBox::Yes){
     //我同意了对方的邀请，现在给对方发送同意的消息 -->服务器 --> 对方客户端
     //我的start按键Enable false 计时器start 棋盘可以点击
     //qDebug()<<"I agree the invite";
         myfdOnServer = myfd;
         qDebug()<<"被邀请者：onJoinOrOnt myfdOnServer:"<<myfdOnServer;
         char AgreeMsg[256] = {0};
         sprintf(AgreeMsg,"#Agree:%d",parterfd);
         ssize_t len = strlen(AgreeMsg);
        if(write(th->sockfd,AgreeMsg,strlen(AgreeMsg)) != len){
            fprintf(stderr,"send AgreeMsg to server:%s\n",strerror(errno));
        }    
     }else if(ret == QMessageBox::No){
     //我拒绝了对方的邀请,给对方发送拒绝的消息
         char disAgreeMsg[256] = {0};
         //附带上对方的fd
         sprintf(disAgreeMsg,"#disAgree:%d",parterfd);
         ssize_t len = strlen(disAgreeMsg);
         if(write(th->sockfd,disAgreeMsg,len) != len){
            fprintf(stderr,"send disagree command：%s\n",strerror(errno));
            exit(1);
         }
     }
 }
 //刷新时间计时器
  void Widget::flushTime(){
      sec++;
      if(sec == 60){
        sec=0;
        min++;
      }
      if(min ==60){
      min=0;
      }
      QString timerstr;
      timerstr.sprintf("TIME: %02d:%02d",min,sec);
      timeLabel->setText(timerstr);

  }
  //对方同意了我的邀请，开始游戏
  void Widget::startGame(int myfd){
    //还原时间
      min = 0;
      sec = 0;
    //时间计时器开启
    timer->start();
    //count 清理
    count = 0;
    //开始键不可用
    startBtn->setEnabled(false);
    //停止闪烁
    killTimer(timerID);
    //清空上局棋子
    if(myfd > 3)myfdOnServer = myfd;
    for(int i=0;i<900;i++){
        chessArea->chessBtn[i/30][i%30]->setIcon(QIcon(""));
        chessArea->chessBtn[i/30][i%30]->setCheckable(true);
        //chessArea->chessBtn[i/30][i%30]->setEnabled(true);
    }
  }
  //收到了对方拒绝我邀请的命令
  void Widget::refuse(){
      QMessageBox::information(this,"对不起！","对方拒绝了你的邀请。",\
                                 QMessageBox::Ok);
  }
  //向服务器发送自己的坐标点
  void Widget::sendMyposition(int pos){
     //在发送端切断已设置过的图标的发送，以免被重新设置ICON 如：对手的棋子又被重设为自己的
      if(chessArea->chessBtn[pos/30][pos%30]->isCheckable() == true){
          char strpos[10] = {0};
          sprintf(strpos,"%d#Pos:%d",myfdOnServer,pos);
          qDebug()<<"on SendMyPosition:"<<myfdOnServer;
          int len = strlen(strpos);
          if(myfdOnServer >= 4){
              if(write(th->sockfd,strpos,len) != len){
                  fprintf(stderr,"send positon msg to server:%s\n",strerror(errno));
                  exit(1);
              }
          }
      }

  }
  //收到坐标点 并开始在相应的位置画图
  void Widget::getPos_and_paintImg(int pos){
      //保存落子上一次的位置
      //本次的闪烁，上一次的设置图标
      count++;
      if(count > 1){
          killTimer(timerID);
      }


      if(count > 1){
          int i = lastTimePos/30;
          int j = lastTimePos%30;

          if(flag == 0){
              //对方的图标 paintingEvent
              imageLabel->flag = 1;
              this->update();
              playerLable->setStyleSheet("*{background-image:url(:/chess2.png);background-position: left top;background-repeat:none; color:#00ff00}");
              chessArea->chessBtn[i][j]->setIcon(QIcon(":/chess2.png"));
              flag = 1;
          }else{
              //我的图标 paintingEvent
              imageLabel->flag = 0;
              this->update();
              playerLable->setStyleSheet("*{background-image:url(:/chess4.png);background-position: left top;background-repeat:none; color:#00ff00}");
              chessArea->chessBtn[i][j]->setIcon(QIcon(":/chess4.png"));
              flag = 0;
          }
      }
      //保留本次的位置
      lastTimePos = pos;
      startTimer(500);

      //设置该按键的可选中属性为false 防止统一个坐标重复设置
      chessArea->chessBtn[pos/30][pos%30]->setCheckable(false);

      }
  //闪烁
  void Widget::timerEvent(QTimerEvent *event){
      timerID = event->timerId();
      if(blinkflag == 0){

          chessArea->chessBtn[lastTimePos/30][lastTimePos%30]\
                  ->setIcon(QIcon(":/chess1.png"));
          blinkflag = 1;
      }else{
          if(flag == 0)
          chessArea->chessBtn[lastTimePos/30][lastTimePos%30]\
                  ->setIcon(QIcon(":/chess2.png"));
          if(flag > 0)
              chessArea->chessBtn[lastTimePos/30][lastTimePos%30]\
                      ->setIcon(QIcon(":/chess4.png"));

          blinkflag = 0;
      }


  }
  void Widget::getWinnerInfo(int winnerFd){
      //按键变亮
      startBtn->setEnabled(true);
      //停止计时器
      timer->stop();

      if(winnerFd == myfdOnServer){
      //自己赢了游戏
          QMessageBox::information(this,"恭喜你！","赢得了本局游戏。",\
                                     QMessageBox::Ok);

      }else{
            if(myfdOnServer == winnerFd-1||myfdOnServer == winnerFd+1){
                //自己输了游戏
                QMessageBox::information(this,"很遗憾！","你输了,再玩一局吧！",\
                                           QMessageBox::Ok);
            }else{
                char winnerInfo[20]={0};
                sprintf(winnerInfo,"本局的赢家是:%d",winnerFd);
                QMessageBox::information(this,"玩家报告！",winnerInfo,\
                                           QMessageBox::Ok);
            }

      }
//      for(int i=0;i<900;i++){
//        chessArea->chessBtn[i/30][i%30]->setEnabled(false);
//      }

  }

Widget::~Widget()
{
}
