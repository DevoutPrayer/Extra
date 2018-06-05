#include "home.h"
#include <QDebug>
Home::Home(QWidget *parent)
    : QWidget(parent)
{
    //setAutoFillBackground(true);
    //resize(300,200);
    //设置窗口大小，并且设置背景图片
    this->setFixedSize(1200,700);
    m_pixmap.load(":/Imgs/1.jpg");
    m_palette.setBrush(this->backgroundRole(),QBrush(m_pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(m_palette);

    //布局
    mainLayout = new QHBoxLayout(this);

    view = new QGraphicsView;
    mainLayout->addWidget(view);

    panel = new QHBoxLayout;

    QVBoxLayout *lcdLayout = new QVBoxLayout;
    QLabel *name = new QLabel;
    name->setText(tr("俄罗斯方块"));
    name->setFont(QFont("Times",35));
    name->setAlignment(Qt::AlignHCenter);
    lcdLayout->addWidget(name);
    scoreLcd = new QLCDNumber;
    scoreLcd->setFixedHeight(90);
    scoreLcd->setFixedWidth(300);
    lcdLayout->addWidget(scoreLcd);

    //按钮栏布局
    QVBoxLayout *btnLayout = new QVBoxLayout;
    startBtn = new QPushButton;
    startBtn->setFixedSize(180,45);
    startBtn->setText(tr("开始"));
    pauseBtn = new QPushButton;
    pauseBtn->setFixedSize(180,45);
    pauseBtn->setText(tr("暂停"));
    reStartBtn = new QPushButton;
    reStartBtn->setFixedSize(180,45);
    reStartBtn->setText(tr("重新开始"));
    endBtn = new QPushButton;
    endBtn->setFixedSize(180,45);
    endBtn->setText(tr("结束游戏"));
    btnLayout->addWidget(startBtn);
    btnLayout->addWidget(pauseBtn);
    btnLayout->addWidget(reStartBtn);
    btnLayout->addWidget(endBtn);
    btnLayout->setAlignment(Qt::AlignHCenter);
    btnLayout->setSpacing(0);
    btnLayout->setMargin(20);

    lcdLayout->addLayout(btnLayout);
    lcdLayout->setAlignment(Qt::AlignCenter);
    lcdLayout->setSpacing(10);

    panel->addLayout(lcdLayout);
    mainLayout->addLayout(panel);
    //mainLayout->setStretch(0,3);
    //mainLayout->setStretch(1,1);
    mainLayout->setMargin(20);

    initGrapicsView();

    connect(startBtn,SIGNAL(clicked(bool)),this,SLOT(slot_startgame()));
    connect(pauseBtn,SIGNAL(clicked(bool)),this,SLOT(slot_pausegame()));
    connect(endBtn,SIGNAL(clicked(bool)),this,SLOT(slot_endgame()));
    connect(reStartBtn,SIGNAL(clicked(bool)),this,SLOT(slot_restartgame()));
}

Home::~Home()
{

}

void Home::slot_endgame()
{
    m_currentBox->slot_stopTimer();
    scoreLcd->display(0);
    m_currentBox->clearFocus();

    m_currentBox->clearBoxGroup(true);
    m_currentBox->setPos(2,2);
    m_nextBox->clearBoxGroup(true);
    foreach(QGraphicsItem *item,m_scene->items(259,19,202,582,Qt::ContainsItemShape,Qt::AscendingOrder))
    {
        m_scene->removeItem(item);
        OnePiece *onePiece = (OnePiece * )item;
        onePiece->deleteLater();
    }
    startBtn->setEnabled(true);
    pauseBtn->setEnabled(false);
    reStartBtn->setEnabled(false);
    endBtn->setEnabled(false);
}

void Home::slot_restartgame()
{
    pause_status = false;
    slot_endgame();
    slot_startgame();
}

void Home::slot_pausegame()
{
    m_currentBox->slot_stopTimer();
    pause_status = true;
    startBtn->setEnabled(true);
    pauseBtn->setEnabled(false);
    endBtn->setEnabled(true);
    reStartBtn->setEnabled(true);

}

void Home::slot_startgame()
{
    if(pause_status)
    {
        m_currentBox->slot_startTimer(1000);
        startBtn->setEnabled(false);
        pauseBtn->setEnabled(true);
        endBtn->setEnabled(true);
        reStartBtn->setEnabled(true);
    }
    else
    {
        m_currentBox->createBox(QPointF(360,40));
        m_nextBox->createBox(QPointF(545,50));
        m_currentBox->setFocus();
        m_currentBox->slot_startTimer(1000);
        startBtn->setEnabled(false);
        pauseBtn->setEnabled(true);
        endBtn->setEnabled(true);
        reStartBtn->setEnabled(true);
    }
}

void Home::initGrapicsView()
{
    view->setRenderHint(QPainter::Antialiasing);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setFixedSize(600,650);
    view->setStyleSheet("background:transparent;border:0;");

    m_scene = new QGraphicsScene;
    m_scene->setSceneRect(0,0,600,650);
    view->setScene(m_scene);
    m_topLine = m_scene->addLine(0,0,600,0);
    m_topLine->setPen(QPen(QColor(255,255,255)));
    m_bottomLine = m_scene->addLine(0,650,600,650);
    m_bottomLine->setPen(QPen(QColor(255,255,255)));
    m_leftLine = m_scene->addLine(0,0,0,650);
    m_leftLine->setPen(QPen(QColor(255,255,255)));
    m_rightLine = m_scene->addLine(600,0,600,650);
    m_rightLine->setPen(QPen(QColor(255,255,255)));

    m_topLine = m_scene->addLine(257,17,463,17);
    m_topLine->setPen(QPen(QColor(255,255,255)));
    m_bottomLine = m_scene->addLine(257,603,463,603);
    m_bottomLine->setPen(QPen(QColor(255,255,255)));
    m_leftLine = m_scene->addLine(257,17,257,603);
    m_leftLine->setPen(QPen(QColor(255,255,255)));
    m_rightLine = m_scene->addLine(463,17,463,603);
    m_rightLine->setPen(QPen(QColor(255,255,255)));

    m_currentBox = new PieceBox;
    m_nextBox = new PieceBox;
    connect(m_currentBox,SIGNAL(signal_needNewBox()),this,SLOT(slot_clearFullRows()));
    connect(m_currentBox,SIGNAL(signal_gameOver()),this,SLOT(slot_gameOver()));
    m_scene->addItem(m_currentBox);
    m_scene->addItem(m_nextBox);
}
void Home::slot_clearFullRows()
{
    m_rowList.clear();
    for(int i = 579;i > 40; i-=20)
    {
        QList<QGraphicsItem *> itemList = m_scene->items(259,i,461,22,Qt::ContainsItemShape,Qt::AscendingOrder);
        if(itemList.count() == 10)
        {
            foreach (QGraphicsItem *item, itemList) {
                OnePiece *piece = (OnePiece *)item;
                QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect;
                piece->setGraphicsEffect(blurEffect);
                QPropertyAnimation *animation = new QPropertyAnimation(piece,"scale");
                animation->setDuration(250);
                animation->setEasingCurve(QEasingCurve::OutBounce);
                animation->setStartValue(4);
                animation->setEndValue(0.25);
                animation->start(QAbstractAnimation::DeleteWhenStopped);
                connect(animation,SIGNAL(finished()),piece,SLOT(deleteLater()));
            }
            //m_mediaPlayer->play();
            m_rowList.append(i);
        }
    }
    if(!m_rowList.isEmpty())
    {
       QTimer::singleShot(300,this,SLOT(slot_moveBox()));
    }else
    {
        m_currentBox->createBox(QPointF(360,40), m_nextBox->getCurrentBoxType());
        m_nextBox->clearBoxGroup(true);
        if(1)
        {
            m_nextBox->createBox(QPointF(545,50));
        }
    }
}

void Home::slot_gameOver()
{
    QMessageBox::information(this,"提示",QString("您的游戏得分为%1!").arg(score),QMessageBox::Yes);
    slot_endgame();

}
void Home::slot_moveBox()
{
    for(int i = m_rowList.count();i>0;i--)
    {
        foreach (QGraphicsItem *item, m_scene->items(259,21,202,m_rowList.at(i-1)-19,Qt::ContainsItemShape,Qt::AscendingOrder)) {
            item->moveBy(0,20);
        }
    }
    slot_update_score(m_rowList.count());
    m_rowList.clear();
    m_currentBox->createBox(QPointF(360,40),m_nextBox->getCurrentBoxType());
    m_nextBox->clearBoxGroup(true);
    m_nextBox->createBox(QPointF(545,50));
}

void Home::slot_update_score(int rows)
{
    score+=rows*100;
    scoreLcd->display(score);
}
