#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include"Stone.h"

class Board : public QWidget{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);

    Stone _s[32];//����32������
    int _r;//���Ӱ뾶
    QPoint center(int,int);//�������ж�Ӧ����������
    QPoint center(int);


    void drawStone(QPainter& ,int);
    void paintEvent(QPaintEvent*);
signals:

public slots:
};


#endif // BOARD_H
