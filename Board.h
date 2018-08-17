#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include"Stone.h"

class Board : public QWidget{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);

    //gama data
    Stone _s[32];//定义32个棋子
    int _r;//棋子半径


    //game status
    int _selectid;
    bool _bRedTurn;//輪流走棋

    //draw functions
    void paintEvent(QPaintEvent*);
    void drawStone(QPainter& ,int);

    //function for coordinate
    QPoint center(int,int);//棋盘行列对应的像素坐标
    QPoint center(int);

    //helpe function
    int getStoneId(int row, int col);

    //move stone
    void mouseReleaseEvent(QMouseEvent*);//捕获鼠标事件
    bool getRowCol(QPoint,int&,int&);//得到鼠标点击的行列

    //rule
    bool canMove(int,int,int,int);
    bool canMoveChe(int,int,int,int);
    bool canMoveMa(int,int,int,int);
    bool canMovePao(int,int,int,int);
    bool canMoveBing(int,int,int,int);
    bool canMoveJiang(int,int,int,int);
    bool canMoveShi(int,int,int,int);
    bool canMoveXiang(int,int,int,int);


    //rule helper
    int relation(int,int,int,int);
    int getStoneCountAtLine(int,int,int,int);

signals:

public slots:
};


#endif // BOARD_H
