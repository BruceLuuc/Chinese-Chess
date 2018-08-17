#ifndef STONE_H
#define STONE_H
#include<QString>

//Stone代表一个棋子
class Stone{
public:
    enum TYPE{JIANG,CHE,PAO,MA,BING,SHI,XIANG};
    void init(int);
    void rotate();//行列中心对称旋转
    QString name();


    int _id;
    int _row;
    int _col;
    TYPE _type;

    bool _dead;
    bool _red;
};

#endif // STONE_H
