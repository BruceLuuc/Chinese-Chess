#ifndef STONE_H
#define STONE_H
#include<QString>

//Stone代表一个棋子
class Stone{
public:
    enum TYPE{JIANG,CHE,PAO,MA,BING,SHI,XIANG};
    int _id;
    int _row;
    int _col;

    TYPE _type;

    bool _dead;
    bool _red;

    void init(int);
    QString getText();
};

#endif // STONE_H
