#ifndef ENUMHEADER_H
#define ENUMHEADER_H

#define PIECE_DIAMETER 20       //小方块的直径
#define PEN_WIDTH 1             //画笔的宽度
#define SPEED 500               //游戏速度
#define ROWSCORE 100            //消除一行得分
//方块box的类型
enum BoxType
{
    IShape = 0,
    JShape,
    LShape,
    OShape,
    SShape,
    TShape,
    Zshape,
    RandomShape
};

enum GameLv
{
    LV0,
    LV1,
    LV2,
    LV3,
    LV4,
    LV5
};

enum GameSpeed
{
    LV0_SPEED = 65535,
    LV1_SPEED = 1000,
    LV2_SPEED = 800,
    LV3_SPEED = 600,
    LV4_SPEED = 400,
    LV5_SPEED = 200
};

#endif // ENUMHEADER_H
