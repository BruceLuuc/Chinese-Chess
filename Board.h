#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include"Stone.h"
#include "Step.h"
#include <QVector>

class Board : public QWidget{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);

    //gama data
    Stone _s[32];//定义32个棋子
    int _r;//棋子半径
    bool _bSide;


    //game status
    int _selectid;
    bool _bRedTurn;//该红棋走了
    void init(bool);

    //draw functions
    void paintEvent(QPaintEvent*);
    void drawPlate(QPainter&);
    void drawPlace(QPainter& );
    void drawInitPosition(QPainter&);
    void drawInitPosition(QPainter&, int, int);
    void drawStone(QPainter&);
    void drawStone(QPainter&,int);

    //function for coordinate
    QPoint center(int,int);//棋盘行列对应的像素坐标
    QPoint center(int);

    //helpe function
    int getStoneId(int row, int col);
    bool isDead(int);
    bool isRed(int id);
    bool sameColor(int id1, int id2);
    void killStone(int id);
    void reliveStone(int id);
    void moveStone(int moveid, int row, int col);

    //move stone
    void mouseReleaseEvent(QMouseEvent*);//捕获鼠标事件
    bool getClickRowCol(QPoint,int&,int&);//得到鼠标点击的行列
    void click(QPoint);
    virtual void click(int,int,int);//人工智能☆
    void trySelectStone(int id);
    void tryMoveStone(int, int, int);
    void moveStone(int moveid, int killid, int row, int col);
    void saveStep(int moveid, int killid, int row, int col, QVector<Step*>& steps);


    //rule
    bool canMove(int,int,int,int);
    bool canMoveChe(int,int,int,int);
    bool canMoveMa(int,int,int,int);
    bool canMovePao(int,int,int,int);
    bool canMoveBing(int,int,int,int);
    bool canMoveJiang(int,int,int,int);
    bool canMoveShi(int,int,int,int);
    bool canMoveXiang(int,int,int,int);

    bool canSelect(int id);

    //rule helper
    int relation(int,int,int,int);
    int getStoneCountAtLine(int,int,int,int);

signals:

public slots:
};


#endif // BOARD_H
