#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(SPACE*17,SPACE*17);
    this->setMouseTracking(true);
    turn = black;
    isOnFocus = false;
    //struct pieces apiece;
    //apiece.pos = QPoint(1,1);
    //apiece.belongTo = white;
    //piece.append(apiece);
    //apiece.pos = QPoint(3,1);
    //apiece.belongTo = black;
    //piece.append(apiece);
    for(int i = 0;i < 15; i++)
        for(int j = 0; j < 15;j++)
            chessPanel[i][j] = NoChess;
    QMenuBar *m_menubar = this->menuBar();
    QMenu *m_menu = new QMenu(tr("  Client  "));
    clientAction = new QAction;
    clientAction->setText(tr("Start"));
    connect(clientAction,SIGNAL(triggered(bool)),this,SLOT(slot_openClient()));
    m_menu->addAction(clientAction);
    m_menubar->addMenu(m_menu);
    m_menu = new QMenu(tr("  Server  "));
    serverAction = new QAction;
    serverAction->setText(tr("Start"));
    connect(serverAction,SIGNAL(triggered(bool)),this,SLOT(slot_openServer()));
    m_menu->addAction(serverAction);
    m_menubar->addMenu(m_menu);
    m_menu = new QMenu(tr("  help  "));
    QAction *m_action = new QAction;
    m_action->setText(tr("about GoBang"));
    m_menu->addAction(m_action);
    m_menubar->addMenu(m_menu);
    connect(this,SIGNAL(chessWin(ChessType)),this,SLOT(slot_chessWin(ChessType)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::slot_chessWin(ChessType x)
{
    QString msg;
    if(x == WhiteChess)
        msg = tr("white win!");
    else
        msg = tr("black win!");
    QMessageBox::information(this,msg,msg);
    for(int i = 0;i < 15; i++)
        for(int j = 0; j < 15;j++)
            chessPanel[i][j] = NoChess;
    piece.clear();
}

void MainWindow::isAnyOneSuccess()
{
    qDebug()<<tr("开始检查");
    bool blackChessFlag = false;
    bool whiteChessFlag = false;
    bool noChessFlag = false;
    for(int j = 0; j < 15; j++)
        for(int i = 0; i < 10;i++)
        {
            /*横向检查*/
            blackChessFlag = false;
            whiteChessFlag = false;
            noChessFlag = false;
            for(int k = 0;k < 5;k++)
            {
                switch (chessPanel[i+k][j]) {
                case NoChess:
                    noChessFlag = true;break;
                case BlackChess:
                    blackChessFlag = true;break;
                case WhiteChess:
                    whiteChessFlag = true;break;
                default:
                    break;
                }
            }
            if(blackChessFlag == true && whiteChessFlag == false&&noChessFlag == false)
                emit chessWin(BlackChess);
            else if(whiteChessFlag == true && blackChessFlag == false&&noChessFlag == false)
                emit chessWin(WhiteChess);
           /*纵向检查*/
            blackChessFlag = false;
            whiteChessFlag = false;
            noChessFlag = false;
            for(int k = 0;k < 5;k++)
            {
                switch (chessPanel[j][i+k]) {
                case NoChess:
                    noChessFlag = true;break;
                case BlackChess:
                    blackChessFlag = true;break;
                case WhiteChess:
                    whiteChessFlag = true;break;
                default:
                    break;
                }
            }
            if(blackChessFlag == true && whiteChessFlag == false&&noChessFlag == false)
                emit chessWin(BlackChess);
            else if(whiteChessFlag == true && blackChessFlag == false&&noChessFlag == false)
                emit chessWin(WhiteChess);
        }
    blackChessFlag = false;
    whiteChessFlag = false;
    noChessFlag = false;
    /*斜着检查*/
    for(int i = 0; i<10;i++)
        for(int j = 0;j<10;j++)
        {
            blackChessFlag = false;
            whiteChessFlag = false;
            noChessFlag = false;
            for(int k = 0;k < 5;k++)
            {
                switch (chessPanel[i+k][j+k]) {
                case NoChess:
                    noChessFlag = true;break;
                case BlackChess:
                    blackChessFlag = true;break;
                case WhiteChess:
                    whiteChessFlag = true;break;
                default:
                    break;
                }
            }
            if(blackChessFlag == true && whiteChessFlag == false&&noChessFlag == false)
                emit chessWin(BlackChess);
            else if(whiteChessFlag == true && blackChessFlag == false&&noChessFlag == false)
                emit chessWin(WhiteChess);
        }
    qDebug()<<tr("检查完成");
}

void MainWindow::slot_canGo()
{
    isAbleGo = true;
}

void MainWindow::slot_peerChessGo(int x,int y)
{
    struct pieces apiece;
    apiece.pos = QPoint(x,y);
    apiece.belongTo = turn;
    if(turn == black)
        chessPanel[x-1][y-1] = BlackChess;
    else
        chessPanel[x-1][y-1] = WhiteChess;
    turn = !turn;
    piece.append(apiece);
    this->repaint();
    isAnyOneSuccess();
    isAbleGo = true;
}
void MainWindow::paintEvent(QPaintEvent *Z)
{
    QPainter painter(this);
    //绘制网格线
    for(char i = 0;i<16;i++)
        painter.drawLine(QPointF(SPACE,SPACE*(i+1)),QPointF(SPACE*16,SPACE*(i+1)));
    for(char i = 0;i<16;i++)
        painter.drawLine(QPointF(SPACE*(i+1),SPACE),QPointF(SPACE*(i+1),SPACE*16));
    if(cursorPos.x()>0&&cursorPos.x()<=16&&cursorPos.y()>0&&cursorPos.y()<=16)
        painter.drawEllipse(QPoint(cursorPos.x()*SPACE,cursorPos.y()*SPACE),10,10);
    for(int i = 0;i<piece.count();i++)
    {
        struct pieces apiece;
        apiece = piece.at(i);
        if(apiece.belongTo == white)
            painter.setBrush(QBrush(QColor(255,255,255)));
        else
            painter.setBrush(QBrush(QColor(0,0,0)));
        painter.drawEllipse(QPoint(apiece.pos.x()*SPACE,apiece.pos.y()*SPACE),20,20);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(isAbleGo)
    {
        if(event->buttons()==Qt::LeftButton)
        {
            if(cursorPos.x()>0&&cursorPos.x()<=16&&cursorPos.y()>0&&cursorPos.y()<=16)
            {
                unsigned char i;
                for(i=0;i<piece.count();i++)
                {
                    struct pieces apiece;
                    apiece = piece.at(i);
                    if(apiece.pos.x()==cursorPos.x()&&apiece.pos.y()==cursorPos.y())
                        break;
                }
                if(i==piece.count())
                {
                    struct pieces apiece;
                    apiece.pos = cursorPos;
                    apiece.belongTo = turn;
                    if(turn == black)
                        chessPanel[cursorPos.x()-1][cursorPos.y()-1] = BlackChess;
                    else
                        chessPanel[cursorPos.x()-1][cursorPos.y()-1] = WhiteChess;
                    turn = !turn;
                    piece.append(apiece);
                    emit signal_chessGo(cursorPos.x(),cursorPos.y());
                    isAbleGo = false;
                    isAnyOneSuccess();
                }
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point;
    //qDebug()<<"鼠标移动！";
    point = event->pos();
    if((point.x()%SPACE<10||point.x()%SPACE>SPACE-10)&&(point.y()%SPACE<10||point.y()>SPACE-10))
    {
        //qDebug()<<"靠近";
        isOnFocus = true;
        if(point.x()%SPACE<10)
            point.setX(point.x()/SPACE);
        else
            point.setX((point.x()+10)/SPACE);
        if(point.y()%SPACE<10)
            point.setY(point.y()/SPACE);
        else
            point.setY((point.y()+10)/SPACE);
        //qDebug()<<point.x()<<","<<point.y();
        cursorPos = point;
        this->repaint();
    }
    else
    {
        isOnFocus = false;
        this->repaint();
        //没有目标在附近
    }
    //qDebug()<<event->pos();
}

void MainWindow::slot_openServer()
{
    serverAction->setEnabled(false);
    clientAction->setEnabled(false);
    isServer = true;
    isClient = false;
    ServerWindow *serverWindow = new ServerWindow();
    serverWindow->show();
    connect(serverWindow,SIGNAL(signal_close()),this,SLOT(slot_ServerClose()));
    connect(serverWindow,SIGNAL(signal_canGo()),this,SLOT(slot_canGo()));
    connect(serverWindow,SIGNAL(signal_peerChessGo(int,int)),this,SLOT(slot_peerChessGo(int,int)));
    connect(this,SIGNAL(signal_chessGo(int,int)),serverWindow,SLOT(slot_ChessGo(int,int)));
}

void MainWindow::slot_openClient()
{
    serverAction->setEnabled(false);
    clientAction->setEnabled(false);
    isServer = false;
    isClient = true;
    ClientWindow *clientWindow = new ClientWindow;
    clientWindow->show();
    connect(clientWindow,SIGNAL(signal_close()),this,SLOT(slot_ClientClose()));
    connect(clientWindow,SIGNAL(signal_canGo()),this,SLOT(slot_canGo()));
    connect(clientWindow,SIGNAL(signal_peerChessGo(int,int)),this,SLOT(slot_peerChessGo(int,int)));
    connect(this,SIGNAL(signal_chessGo(int,int)),clientWindow,SLOT(slot_chessGo(int,int)));
}

void MainWindow::slot_ServerClose()
{
    serverAction->setEnabled(true);
    clientAction->setEnabled(true);
    isServer = false;
    isClient = false;
    qDebug()<<"服务器关闭！";
}

void MainWindow::slot_ClientClose()
{
    serverAction->setEnabled(true);
    clientAction->setEnabled(true);
    isServer = false;
    isClient = false;
    qDebug()<<"客户端关闭！";
}
