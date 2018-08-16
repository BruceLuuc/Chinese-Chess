#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include"Stone.h"

class Board : public QWidget{
    Q_OBJECT
public:
    Stone _s[32];//����32������
    int _r;//���Ӱ뾶
    int _selectid;
    bool _bRedTurn;

    explicit Board(QWidget *parent = 0);
    QPoint center(int,int);//�������ж�Ӧ����������
    QPoint center(int);

    void drawStone(QPainter& ,int);
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    bool getRowCol(QPoint,int&,int&);
    bool canMove(int,int,int,int);
    bool canMove1(int,int,int,int);
    bool canMove2(int,int,int,int);
    bool canMove3(int,int,int,int);
    bool canMove4(int,int,int,int);
    bool canMove5(int,int,int,int);
    bool canMove6(int,int,int,int);
    bool canMove7(int,int,int,int);
signals:

public slots:
};


#endif // BOARD_H
