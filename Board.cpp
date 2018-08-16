#include "Board.h"
#include<QPainter>

Board::Board(QWidget *parent) : QWidget(parent){
    this->resize( QSize( 700, 660 ));//修改默认窗口大小
    for(int i=0;i!=32;++i)
        _s[i].init(i);

}

void Board::paintEvent(QPaintEvent*){
    QPainter painter(this);
    int d=60;//棋盘直径
    _r=d/2;
    //画10条横线
    for(int i=1;i<=10;++i)
        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    for(int i=1;i<=9;++i)
        if(i==1||i==9)
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,10*d));
        else{
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
            painter.drawLine(QPoint(i*d,6*d),QPoint(i*d,10*d));
        }

    //九宫格
    painter.drawLine(QPoint(4*d,1*d),QPoint(6*d,3*d));
    painter.drawLine(QPoint(6*d,1*d),QPoint(4*d,3*d));

    painter.drawLine(QPoint(4*d,8*d),QPoint(6*d,10*d));
    painter.drawLine(QPoint(6*d,8*d),QPoint(4*d,10*d));

    //绘制32个棋子
    for(int i=0;i<32;++i)
        drawStone(painter,i);

}

QPoint Board::center(int row,int col){
    QPoint ret;
    ret.rx()=(col+1)*_r*2;
    ret.ry()=(row+1)*_r*2;
    return ret;
}
QPoint Board::center(int id){
    return center(_s[id]._row,_s[id]._col);
}

void Board::drawStone(QPainter&painter,int id){
    QPoint c=center(id);
    QRect rect= QRect(c.x()-_r,c.y()-_r,_r*2,_r*2);
    painter.setBrush(QBrush(QColor(255,255,0)));
    painter.setPen(Qt::black);
    painter.drawEllipse(center(id),_r,_r);
    if(_s[id]._red)
        painter.setPen(Qt::red);
    painter.setFont(QFont("system",_r,700));
    painter.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));
}
