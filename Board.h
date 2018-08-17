#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include"Stone.h"

class Board : public QWidget{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);

    //gama data
    Stone _s[32];//����32������
    int _r;//���Ӱ뾶


    //game status
    int _selectid;
    bool _bRedTurn;//݆������

    //draw functions
    void paintEvent(QPaintEvent*);
    void drawStone(QPainter& ,int);

    //function for coordinate
    QPoint center(int,int);//�������ж�Ӧ����������
    QPoint center(int);

    //helpe function
    int getStoneId(int row, int col);

    //move stone
    void mouseReleaseEvent(QMouseEvent*);//��������¼�
    bool getRowCol(QPoint,int&,int&);//�õ������������

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
