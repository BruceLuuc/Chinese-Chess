#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include"Board.h"

class SingleGame:public Board
{
public:
    SingleGame(){_level=3;}
    virtual void click(int,int,int);//ÈË¹¤ÖÇÄÜ¡î
    Step* getBestMove();
    void getAllPossibleMove(QVector<Step*>& steps);
    void fakeMove(Step*step);
    void unfakeMove(Step*step);
    int calcScore();

    int getMinScore();
    int getMaxScore();
    int _level;
};

#endif // SINGLEGAME_H
