#include "Board.h"
#include<QPainter>
#include<QMouseEvent>
#include <QDebug>
#define GetRowCol(__row, __col, __id) \
    int __row = _s[__id]._row;\
    int __col = _s[__id]._col

Board::Board(QWidget *parent) : QWidget(parent){
    _r=30;//初始化棋子半径，棋盘间隔
    this->resize( QSize( 700, 680 ));//修改默认窗口大小
    init(false);
}
void Board::init(bool bRedSide){
    //初始化32个棋子 id编号0-31
    for(int i=0; i!=32; ++i)
        _s[i].init(i);

    if(bRedSide)
        for(int i=0; i<32; ++i)
            _s[i].rotate();

    _selectid = -1;
    _bRedTurn = true;//红棋先走
    _bSide = bRedSide;
}
void Board::paintEvent(QPaintEvent*){

    QPainter painter(this);
    int d=2*_r;//棋盘直径
    //绘制棋盘
    for(int i=1;i<=10;++i)
        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    for(int i=1;i<=9;++i)
        if(i==1||i==9)
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,10*d));
        else{
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
            painter.drawLine(QPoint(i*d,6*d),QPoint(i*d,10*d));
        }

    //绘制X 九宫格
    painter.drawLine(QPoint(4*d,1*d),QPoint(6*d,3*d));
    painter.drawLine(QPoint(6*d,1*d),QPoint(4*d,3*d));

    painter.drawLine(QPoint(4*d,8*d),QPoint(6*d,10*d));
    painter.drawLine(QPoint(6*d,8*d),QPoint(4*d,10*d));

    //楚河汉界
    painter.setFont(QFont("腾祥范笑歌楷书繁",1.1*_r,800));
    painter.drawText(2*d, 5.8*d, "楚  河    汉  界");

    //绘制32个棋子
    drawStone(painter);
}

bool Board::isDead(int id){
    if(id == -1)return true;
    return _s[id]._dead;
}

QPoint Board::center(int row,int col){
    QPoint ret;
    ret.rx()=(col+1)*_r*2;//row col下标从0开始
    ret.ry()=(row+1)*_r*2;//所以要加上一
    return ret;
}
QPoint Board::center(int id){
    return center(_s[id]._row,_s[id]._col);
}
void Board::drawStone(QPainter &p){
    for(int i=0; i<32; i++)
        drawStone(p, i);
}
void Board::drawStone(QPainter&painter,int id){
    if(isDead(id))
        return;
    QPoint c=center(id);
    QRect rect= QRect(c.x()-_r,c.y()-_r,_r*2,_r*2);
    if(id==_selectid)
        painter.setBrush(QBrush(QColor(250,100,10)));
    else
        painter.setBrush(QBrush(QColor(250,200,100)));
    painter.setPen(Qt::black);
    painter.drawEllipse(center(id),_r,_r);
    if(isRed(id))
        painter.setPen(Qt::red);
    painter.setFont(QFont("禹卫书法行书繁体",1.1*_r,800));//象棋字体 华文新魏  腾祥范笑歌楷书繁 方正北魏楷书繁体
    painter.drawText(rect,_s[id].name(),QTextOption(Qt::AlignCenter));
}

//复杂度高O(N*2)
//传进来pt点，返回row,col,所以要用引用
bool Board::getClickRowCol(QPoint pt,int &row,int&col){
    for(row=0;row!=10;++row)
        for(col=0;col!=9;++col){
            QPoint c=center(row,col);
            int dx=c.x()-pt.x();
            int dy=c.y()-pt.y();
            int distance=dx*dx+dy*dy;
            if(distance<_r*_r)
                return true;
        }
    return false;
}
bool Board::isRed(int id){
    return _s[id]._red;
}
bool Board::sameColor(int id1, int id2){
    if(id1 == -1 || id2 == -1) return false;
    return isRed(id1) == isRed(id2);
}
bool Board::canSelect(int id){
    return _bRedTurn == _s[id]._red;
}
void Board::trySelectStone(int id){
    if(id == -1)
        return;
    if(!canSelect(id)) return;
    _selectid = id;
    update();
}
void Board::moveStone(int moveid, int row, int col)
{
    _s[moveid]._row = row;
    _s[moveid]._col = col;

    _bRedTurn = !_bRedTurn;
}
void Board::killStone(int id){
    if(id==-1) return;
    _s[id]._dead = true;
}
void Board::moveStone(int moveid, int killid, int row, int col){
    killStone(killid);
    moveStone(moveid, row, col);
}
void Board::tryMoveStone(int killid, int row, int col){
    if(killid != -1 && sameColor(killid, _selectid)){
        trySelectStone(killid);
        return;
    }
    bool ret = canMove(_selectid, row, col,killid);
    if(ret){
        moveStone(_selectid, killid, row, col);
        _selectid = -1;
        update();
    }
}
void Board::click(int id, int row, int col){
    if(this->_selectid == -1)
        trySelectStone(id);
    else
        tryMoveStone(id, row, col);
}
void Board::click(QPoint pt){
    int row, col;
    bool bClicked = getClickRowCol(pt, row, col);
    if(!bClicked) return;

    int id = getStoneId(row, col);
    click(id, row, col);
}
void Board::mouseReleaseEvent(QMouseEvent*ev){
    if(ev->button() != Qt::LeftButton) return;
    click(ev->pos());
}

bool Board::canMove(int moveid,int row,int col,int killid){
    if(sameColor(moveid, killid)){
        //换选择
        //_selectid=killid;
        //update();
        return false;
    }
    switch (_s[moveid]._type) {
    case Stone::JIANG:
        return canMoveJiang(moveid, row, col, killid);
        break;
    case Stone::SHI:
        return canMoveShi(moveid, row, col, killid);
        break;
    case Stone::XIANG:
        return canMoveXiang(moveid, row, col, killid);
        break;
    case Stone::CHE:
        return canMoveChe(moveid, row, col, killid);
        break;
    case Stone::MA:
        return canMoveMa(moveid, row, col, killid);
        break;
    case Stone::PAO:
        return canMovePao(moveid, row, col, killid);
        break;
    case Stone::BING:
        return canMoveBing(moveid, row, col, killid);
        break;
    }
    return true;
}

int Board::relation(int row1, int col1, int row, int col){
    return qAbs(row1-row)*10+qAbs(col1-col);
}
//row col 是killid的
bool Board::canMoveJiang(int moveid, int row, int col, int killid){
    //将 走位九宫格之内
    //步长是一个格子
    if(killid != -1 && _s[killid]._type == Stone::JIANG)
        return canMoveChe(moveid, killid, row, col);

    GetRowCol(rol1,col1,moveid);
    int r=relation(rol1,col1,row,col);
    if(r != 1 && r != 10) return false;

    if(col < 3||col > 5) return false;
    if(isRed(moveid)){
        if(row > 2)
            return false;
    }else if(row < 7)
        return false;
    return true;
}
bool Board::canMoveShi(int moveid, int row, int col, int killid){
    //士
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r!=11)
        return false;
    if(isRed(moveid)){
        if(row > 2)
            return false;
    }else if(row < 7)
        return false;
    if(col < 3||col > 5) return false;

    return true;
}

//通过行列值反向判断该(row,col)位置上有没有棋子,有的话返回该棋子编号
int Board::getStoneId(int row, int col){
    for(int i=0; i<32; ++i)
        if(_s[i]._row == row && _s[i]._col == col && !_s[i]._dead)
            return i;
    return -1;
}
bool Board::canMoveXiang(int moveid, int row, int col, int killid){
    //相
    if(isRed(moveid)){
        if(row > 5)
            return false;
    }else if(row < 4)
        return false;
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 22) return false;

    int rEye = (row+row1)/2;
    int cEye = (col+col1)/2;
    if(getStoneId(rEye, cEye) != -1)
        return false;

    return true;
}
//判断直线上有没有其他棋子 返回棋子个数ret
int Board::getStoneCountAtLine(int row1,int col1,int row2,int col2){
    int ret=0;
    if(row1!=row2&&col1!=col2)return -1;//行列都不相同
    if(row1==row2&&col1==col2)return -1;//同一个点
    if(row1==row2){
        int min=col1<col2?col1:col2;
        int max=col1<col2?col2:col1;
        for(int col=min+1;col!=max;++col)
            if(getStoneId(row1,col)!=-1)
                ++ret;
    }else{
        int min = row1 < row2 ? row1 : row2;
        int max = row1 < row2 ? row2 : row1;
        for(int row = min+1; row<max; ++row)
            if(getStoneId(row, col1) != -1)
                ++ret;
    }
    return ret;
}
bool Board::canMoveChe(int moveid, int row, int col, int killid){
    //车
    GetRowCol(row1, col1, moveid);
    int ret = getStoneCountAtLine(row1, col1, row, col);
    if(ret == 0)
        return true;
    return false;
}
bool Board::canMoveMa(int moveid, int row, int col, int killid){
    //马
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 12&&r!=21) return false;
    if(r==12)
        if(getStoneId(row1,(col+col1)/2)!=-1)
            return false;
    if(r==21)
        if(getStoneId((row+row1)/2,col1)!=-1)
            return false;

    return true;
}
//row col 是killid的
bool Board::canMovePao(int moveid, int row, int col, int killid){
    //炮
    GetRowCol(row1, col1, moveid);
    int ret = getStoneCountAtLine(row, col, row1, col1);
    if(killid != -1){
        //如果killid选中了一个棋子
        //中间只有一个棋子
        if(ret == 1) return true;
    }else{
        //没选棋子 直行走棋 中间相隔0个棋子
        if(ret == 0) return true;
    }
    return false;


}
bool Board::canMoveBing(int moveid, int row, int col, int killid){
    //兵
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 1 && r != 10) return false;

    if(isRed(moveid)){
        if(row1<=4){//没过河之前
            if(row1>=row)
                return false;
        }else{
            if(row<=4)//过河之后就不能回去了
                return false;
        }

    }else{
        if(row1>=5){
            if(row1<=row)
                return false;
        }else{
            if(row>=5)
                return false;
        }
    }
    return true;
}
