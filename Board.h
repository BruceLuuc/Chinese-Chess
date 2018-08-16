#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include"Stone.h"

class Board : public QWidget{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);

    Stone _s[32];//定义32个棋子
    int _r;//棋子半径
    QPoint center(int,int);//棋盘行列对应的像素坐标
    QPoint center(int);


    void drawStone(QPainter& ,int);
    void paintEvent(QPaintEvent*);
signals:

public slots:
};


#endif // BOARD_H
