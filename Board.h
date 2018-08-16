#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include"Stone.h"

class Board : public QWidget{
    Q_OBJECT
public:
    Stone _s[32];//定义32个棋子
    int _r;//棋子半径
    int _selectid;
    bool _bRedTurn;//輪流走棋

    explicit Board(QWidget *parent = 0);
    QPoint center(int,int);//棋盘行列对应的像素坐标
    QPoint center(int);

    void drawStone(QPainter& ,int);
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);//捕获鼠标事件
    bool getRowCol(QPoint,int&,int&);//得到鼠标点击的行列
    bool canMove(int,int,int,int);
    bool canMove1(int,int,int,int);
    bool canMove2(int,int,int,int);
    bool canMove3(int,int,int,int);
    bool canMove4(int,int,int,int);
    bool canMove5(int,int,int,int);
    bool canMove6(int,int,int,int);
    bool canMove7(int,int,int,int);

    int relation(int,int,int,int);
    int getStoneId(int row, int col);
    int getStoneCountAtLine(int,int,int,int);

signals:

public slots:
};


#endif // BOARD_H
