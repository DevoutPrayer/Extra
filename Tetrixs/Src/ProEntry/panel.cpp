#include "panel.h"
#include "ui_panel.h"
#include "enumHeader.h"
#include <QDebug>
#include <QGraphicsBlurEffect>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QMediaContent>

Panel::Panel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Panel)
{
    ui->setupUi(this);
    m_isPauseGame = false;
    m_isGameOver = false;

    m_mediaPlayer = new QMediaPlayer;
    m_mediaPlayer->setMedia(QUrl::fromLocalFile(QString("clearRow.mp3")));
    m_mediaPlayer->setVolume(100);
    //设置背景
    setbackground(LV0);
    initControlWidget();

    initGraphicsViewWidget();
}

Panel::~Panel()
{
    delete ui;
}

void Panel::setbackground(const int &Lv)
{
    setAutoFillBackground(true);
    switch (Lv) {
    case LV0:
        m_currentLv = LV0;
        m_currentLVSpeed = LV0_SPEED;
        ui->label_gameLevel->setText("俄罗斯方块");
        m_pixmap.load(":/background/Image/background/background.png");
        break;
    case LV1:
        m_currentLv = LV1;
        m_currentLVSpeed = LV1_SPEED;
        ui->label_gameLevel->setText("第一关");
        m_pixmap.load(":/background/Image/background/background01.png");
        break;
    case LV2:
        m_currentLv = LV2;
        m_currentLVSpeed = LV2_SPEED;
        ui->label_gameLevel->setText("第二关");
        m_pixmap.load(":/background/Image/background/background02.png");
        break;
    case LV3:
        m_currentLv = LV3;
        m_currentLVSpeed = LV3_SPEED;
        ui->label_gameLevel->setText("第三关");
        m_pixmap.load(":/background/Image/background/background03.png");
        break;
    case LV4:
        m_currentLv = LV4;
        m_currentLVSpeed = LV4_SPEED;
        ui->label_gameLevel->setText("第四关");
        m_pixmap.load(":/background/Image/background/background04.png");
        break;
    case LV5:
        m_currentLv = LV5;
        m_currentLVSpeed = LV5_SPEED;
        ui->label_gameLevel->setText("第五关");
        m_pixmap.load(":/background/Image/background/background05.png");
        break;
    default:
        break;
    }
    m_Palette.setBrush(QPalette::Window, QBrush(m_pixmap.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    setPalette(m_Palette);
}

void Panel::initControlWidget()
{
    switch (m_currentLv) {
    case LV0:
        ui->pbt_startGame->setEnabled(true);
        ui->pbt_pauseGame->setEnabled(false);
        ui->pbt_restart->setEnabled(false);
        ui->pbt_stopGame->setEnabled(false);
        break;
    case LV1:
    case LV2:
    case LV3:
    case LV4:
    case LV5:
        ui->pbt_startGame->setEnabled(false);
        ui->pbt_pauseGame->setEnabled(true);
        ui->pbt_restart->setEnabled(true);
        ui->pbt_stopGame->setEnabled(true);
        break;
    default:
        break;
    }
}

void Panel::initGraphicsViewWidget()
{
    //使用抗锯齿渲染
    ui->GraphicsView->setRenderHint(QPainter::Antialiasing);
    //设置缓冲背景，加速渲染
    ui->GraphicsView->setCacheMode(QGraphicsView::CacheBackground);

    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(30,30,310,410);
    ui->GraphicsView->setScene(m_scene);

    //方块可移动的四条线
    //向外扩展3像素，这样可以使方块组到达边界的时候再移动就会发生碰撞
    m_topLine = m_scene->addLine(32,32,238,32);
    m_leftLine = m_scene->addLine(32,32,32,438);
    m_buttomLine = m_scene->addLine(32,438,238,438);
    m_rightLine = m_scene->addLine(238,32,238,438);

    m_topLine->setPen(QPen(QColor(255,255,255)));
    m_leftLine->setPen(QPen(QColor(255,255,255)));
    m_buttomLine->setPen(QPen(QColor(255,255,255)));
    m_rightLine->setPen(QPen(QColor(255,255,255)));

    m_currentBox = new pieceBox;
    m_nextBox = new pieceBox;
    connect(m_currentBox,SIGNAL(signal_needNewBox()),this,SLOT(slot_clearFullRows()));
    connect(m_currentBox,SIGNAL(signal_gameOver()),this,SLOT(slot_gameOver()));
    m_scene->addItem(m_currentBox);
    m_scene->addItem(m_nextBox);
}

void Panel::startGame()
{
    m_currentBox->createBox(QPointF(135,55));
    m_nextBox->createBox(QPointF(290,55));
    //将键盘焦点给当前的方块组
    m_currentBox->setFocus();
    m_currentBox->slot_startTimer(m_currentLVSpeed);
}

void Panel::updateScore(const int fullRows)
{
    int score = ui->LCDNum_Score->value() + fullRows*ROWSCORE;

    ui->LCDNum_Score->display(score);
    if(score < 1000)         //第一关
    {

    }else if(score < 2000)  //第二关
    {
        setbackground(LV2);
        initControlWidget();
        m_currentBox->slot_stopTimer();
        m_currentBox->slot_startTimer(m_currentLVSpeed);
    }else if(score < 4000)  //第三关
    {
        setbackground(LV3);
        initControlWidget();
        m_currentBox->slot_stopTimer();
        m_currentBox->slot_startTimer(m_currentLVSpeed);
    }else if(score < 8000) //第四关
    {
        setbackground(LV4);
        initControlWidget();
        m_currentBox->slot_stopTimer();
        m_currentBox->slot_startTimer(m_currentLVSpeed);
    }else if(score < 16000)  //第五关
    {
        setbackground(LV5);
        initControlWidget();
        m_currentBox->slot_stopTimer();
        m_currentBox->slot_startTimer(m_currentLVSpeed);
    }else   //从第一关重新开始
    {
        setbackground(LV1);
        initControlWidget();
        m_currentBox->slot_stopTimer();
        m_currentBox->slot_startTimer(m_currentLVSpeed);
    }
}

/**
 *  开始游戏
 * @brief Panel::on_pbt_startGame_clicked
 */

void Panel::on_pbt_startGame_clicked()
{
    m_isGameOver = false;
    if(m_isPauseGame)
    {
        ui->pbt_startGame->setEnabled(false);
        m_isPauseGame = false;
        m_currentBox->slot_startTimer(m_currentLVSpeed);
        return;
    }
    //默认等级为LV1
    setbackground(LV1);
    initControlWidget();

    startGame();
}

/**
 *  暂停游戏
 * @brief Panel::on_pbt_pauseGame_clicked
 */
void Panel::on_pbt_pauseGame_clicked()
{
    if(m_isPauseGame)
    {
        return;
    }
    m_isPauseGame = true;
    m_currentBox->slot_stopTimer();
    ui->pbt_startGame->setEnabled(true);
    QMessageBox::information(this,"提示","暂停游戏！",QMessageBox::Yes);
}

/**
 * 重新开始游戏
 * @brief Panel::on_pbt_restart_clicked
 */
void Panel::on_pbt_restart_clicked()
{

    m_currentBox->slot_stopTimer();
    m_currentBox->clearBoxGroup();
    m_nextBox->clearBoxGroup(true);
    //先将当前的小正方形组移出游戏框，防止下面的清除item将该方块组清除了
    m_currentBox->setPos(290,55);
    ui->LCDNum_Score->display(0);

    //清空视图中所有的小方块
    foreach (QGraphicsItem *item, m_scene->items(34, 34, 204, 404, Qt::ContainsItemShape,Qt::AscendingOrder)) {
        // 先从场景中移除小方块，因为使用deleteLater()是在返回主事件循环后才销毁
        // 小方块的，为了在出现新的方块组时不发生碰撞，所以需要先从场景中移除小方块
        m_scene->removeItem(item);
        onePiece *piece = (onePiece*) item;
        piece->deleteLater();
    }
    m_isPauseGame = false;
    on_pbt_startGame_clicked();
}

/**
 *  停止游戏
 * @brief Panel::on_pbt_stopGame_clicked
 */
void Panel::on_pbt_stopGame_clicked()
{
    m_currentBox->slot_stopTimer();
    slot_gameOver();
}

/**清除满行的小方块
 * @brief Panel::slot_clearFullRows
 */
void Panel::slot_clearFullRows()
{
    m_rowList.clear();
    //获取比一行方格多行的所有小方块,不包含最高的一行
    for(int i = 414;i > 35; i-=20)
    {
        //返回可视区域(202*22)内所有的完全可视的item
        QList<QGraphicsItem *> itemList = m_scene->items(34,i,204,22,Qt::ContainsItemShape,Qt::AscendingOrder);
//        qDebug() << "可是区域内的item数：" << itemList.count();
        //已满
        if(itemList.count() == 10)
        {
            //遍历列表删除小方块
            foreach (QGraphicsItem *item, itemList) {
                onePiece *piece = (onePiece *)item;

                //模糊效果，先放大再缩小
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
            m_mediaPlayer->play();
            //记录满行的行地址
            m_rowList.append(i);
        }
    }
//    qDebug() << "满行的行数：" << m_rowList.size();
    //存在满行，删除后将上面的方块下移
    if(!m_rowList.isEmpty())
    {
        //等待所有的小正方形都销毁后再将上方的小正方形向下移动
       QTimer::singleShot(300,this,SLOT(slot_moveBox()));
    }else   //直接创建新的方块组
    {
        m_currentBox->createBox(QPointF(135,55), m_nextBox->getCurrentBoxType());
        // 清空并销毁提示方块组中的所有小方块
        m_nextBox->clearBoxGroup(true);
        if(!m_isGameOver)
        {
            m_nextBox->createBox(QPointF(290,55));
        }
    }
}

void Panel::slot_gameOver()
{
//    qDebug() << "game over";
    m_isGameOver = true;
    QMessageBox::information(this,"提示",QString("您的游戏得分为%1!").arg(ui->LCDNum_Score->value()),QMessageBox::Yes);
    ui->LCDNum_Score->display(0);
    m_currentBox->clearFocus();

    setbackground(LV0);
    initControlWidget();
    m_isPauseGame = false;
    //初始化界面
    m_currentBox->clearBoxGroup(true);
    m_nextBox->clearBoxGroup(true);
    //先将当前的小正方形组移出游戏框，防止下面的清除item将该方块组清除了
    m_currentBox->setPos(290,55);
    //清空视图中所有的小方块
    foreach (QGraphicsItem *item, m_scene->items(34, 34, 204, 404, Qt::ContainsItemShape,Qt::AscendingOrder)) {
        // 先从场景中移除小方块，因为使用deleteLater()是在返回主事件循环后才销毁
        // 小方块的，为了在出现新的方块组时不发生碰撞，所以需要先从场景中移除小方块
        m_scene->removeItem(item);
        onePiece *piece = (onePiece*) item;
        piece->deleteLater();
    }
}

/**清空满行的小方块后向下移动上面的小方块
 * @brief Panel::slot_moveBox
 */
void Panel::slot_moveBox()
{
    // 从位置最靠上的满行开始
    for (int i = m_rowList.count(); i > 0; i--)
    {
        foreach (QGraphicsItem *item, m_scene->items(34, 34, 206, m_rowList.at(i-1) - 32, Qt::ContainsItemShape,Qt::AscendingOrder)) {
            item->moveBy(0, 20);
        }
    }
    // 更新分数
    updateScore(m_rowList.count());
    // 将满行列表清空为0
    m_rowList.clear();

    // 等所有行下移以后再出现新的方块组
    m_currentBox->createBox(QPointF(135,55), m_nextBox->getCurrentBoxType());
    // 清空并销毁提示方块组中的所有小方块
    m_nextBox->clearBoxGroup(true);
    m_nextBox->createBox(QPointF(290,55));

}
