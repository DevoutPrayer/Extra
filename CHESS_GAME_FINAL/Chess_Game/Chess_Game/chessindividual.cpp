#include "chessindividual.h"

ChessIndividual::ChessIndividual(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *glayout = new QGridLayout;

    glayout->setSpacing(0);
    glayout->setMargin(5);
    //有半边的900按钮
    //添加按键组
     BtnGroup = new QButtonGroup(this);
    int i,j;
    for(i=0;i<30;i++){
        for(j=0;j<30;j++){
            chessBtn[i][j]=  new QPushButton(this);
            //通过判断这个checkable的属性，来确定这个键是不是已经设置了图标，即:是不是已落子
            //它的默认值为false,现在把它改为true
            chessBtn[i][j]->setCheckable(true);
            chessBtn[i][j]->setStyleSheet("border-radius:15px;border-top:1px dashed #000000;border-left:1px dashed #000000;background-color:#F5F5DC;");
            if(i == 29){
                chessBtn[i][j]->setStyleSheet("border-radius:15px;border-bottom:1px dashed #000000;border-top:1px dashed #000000;border-left:1px dashed #000000;background-color:#F5F5DC;");
            }else if(j == 29){
                chessBtn[i][j]->setStyleSheet("border-radius:15px;border-right:1px dashed #000000;border-top:1px dashed #000000;border-left:1px dashed #000000;background-color:#F5F5DC;");
            }

            BtnGroup->addButton(chessBtn[i][j],i*30+j);
            chessBtn[i][j]->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
            chessBtn[i][j]->setCursor(Qt::PointingHandCursor);
            glayout->addWidget(chessBtn[i][j],i,j);

        }
    }
    chessBtn[29][29]->setStyleSheet("border-radius:15px;border:1px dashed #000000;background-color:#F5F5DC;");
    setLayout(glayout);
}

