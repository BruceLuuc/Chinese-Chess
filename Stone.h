#ifndef STONE_H
#define STONE_H
#include<QString>

//Stone����һ������
class Stone{
public:
    enum TYPE{CHE,MA,PAO,BING,JIANG,SHI,XIANG};
    void init(int);
    void rotate();//�������ĶԳ���ת
    QString name();


    int _id;
    int _row;
    int _col;
    TYPE _type;

    bool _dead;
    bool _red;
};

#endif // STONE_H
