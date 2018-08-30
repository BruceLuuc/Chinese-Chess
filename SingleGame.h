#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include"Board.h"

class SingleGame:public Board
{
    Q_OBJECT
public:
    SingleGame():_level(4){}
    virtual void click(int,int,int);//ÈË¹¤ÖÇÄÜ¡î
    Step* getBestMove();
    void getAllPossibleMove(QVector<Step*>& steps);
    void fakeMove(Step*step);
    void unfakeMove(Step*step);
    int calcScore();

    int getMinScore(int level,int curMaxScore);
    int getMaxScore(int level,int curMinScore);
    int AlphaBeta(int level,int preScore);
    int _level;
public slots:
    void computerMove();
};

#endif // SINGLEGAME_H
