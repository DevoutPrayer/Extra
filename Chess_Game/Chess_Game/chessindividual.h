#ifndef CHESSINDIVIDUAL_H
#define CHESSINDIVIDUAL_H
#include <QWidget>
#include <QPushButton>
#include <QStackedLayout>
#include <QButtonGroup>
#include <QPixmap>



class ChessIndividual : public QWidget
{
    Q_OBJECT
public:
    explicit ChessIndividual(QWidget *parent = 0);
    //按键组
    QButtonGroup *BtnGroup;
    //900个按键
    QPushButton *chessBtn[30][30];


};

#endif // CHESSINDIVIDUAL_H
