#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include"Board.h"

class SingleGame:public Board
{
public:
    virtual void click(int,int,int);//ÈË¹¤ÖÇÄÜ¡î
    void computerMove();
    void getAllPossibleMove(QVector<Step*>& steps);
};

#endif // SINGLEGAME_H
