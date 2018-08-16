#include "Board.h"
#include<QPainter>
#include<QMouseEvent>

Board::Board(QWidget *parent) : QWidget(parent){
    _r=30;//��ʼ�����Ӱ뾶�����̼��
    _selectid=-1;
    _bRedTurn=true;
    this->resize( QSize( 700, 680 ));//�޸�Ĭ�ϴ��ڴ�С
    //��ʼ��32������ id���0-31
    for(int i=0;i!=32;++i)
        _s[i].init(i);

}

void Board::paintEvent(QPaintEvent*){
    QPainter painter(this);
    int d=2*_r;//����ֱ��

    //��������
    for(int i=1;i<=10;++i)
        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    for(int i=1;i<=9;++i)
        if(i==1||i==9)
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,10*d));
        else{
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
            painter.drawLine(QPoint(i*d,6*d),QPoint(i*d,10*d));
        }

    //����X �Ź���
    painter.drawLine(QPoint(4*d,1*d),QPoint(6*d,3*d));
    painter.drawLine(QPoint(6*d,1*d),QPoint(4*d,3*d));

    painter.drawLine(QPoint(4*d,8*d),QPoint(6*d,10*d));
    painter.drawLine(QPoint(6*d,8*d),QPoint(4*d,10*d));

    //���Ӻ���
    painter.setFont(QFont("���鷶Ц�迬�鷱",1.1*_r,800));
    painter.drawText(2*d, 5.8*d, "��  ��    ��  ��");

    //����32������
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
    if(_s[id]._dead)
        return;
    QPoint c=center(id);
    QRect rect= QRect(c.x()-_r,c.y()-_r,_r*2,_r*2);
    if(id==_selectid)
        painter.setBrush(QBrush(QColor(250,100,10)));
    else
        painter.setBrush(QBrush(QColor(250,200,100)));
    painter.setPen(Qt::black);
    painter.drawEllipse(center(id),_r,_r);
    if(_s[id]._red)
        painter.setPen(Qt::red);
    painter.setFont(QFont("�����鷨���鷱��",1.1*_r,800));//�������� ������κ  ���鷶Ц�迬�鷱 ������κ���鷱��
    painter.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));
}

//���Ӷȸ�O(N*2)
bool Board::getRowCol(QPoint pt,int &row,int&col){
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
bool Board::canMove1(int moveid, int row, int col, int killid){
    //�� ��λ�Ź���֮��
    //������һ������
    if(_s[moveid]._red){
        if(row > 2)
            return false;
    }else if(row < 7)
        return false;
    if(col < 3) return false;
    if(col > 5) return false;

    //���в��Ȼ��һ������0
    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = abs(dr)*10 + abs(dc); // 12, 21   22   10, 1
    if(d == 1 || d == 10)
        return true;
    return false;
}
bool Board::canMove2(int moveid, int row, int col, int killid){
    if(_s[moveid]._red){
        if(row > 2)
            return false;
    }else if(row < 7)
        return false;
    if(col < 3) return false;
    if(col > 5) return false;

    //���в��Ȼ��һ������0
    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = abs(dr)*10 + abs(dc); // 12, 21   22   10, 1
    if(d==11)
        return true;
    return false;
}
bool Board::canMove3(int moveid, int row, int col, int killid){
    return true;
}
bool Board::canMove4(int moveid, int row, int col, int killid){
    return true;
}
bool Board::canMove5(int moveid, int row, int col, int killid){
    return true;
}
bool Board::canMove6(int moveid, int row, int col, int killid){
    return true;
}
bool Board::canMove7(int moveid, int row, int col, int killid){
    return true;
}
bool Board::canMove(int moveid,int row,int col,int killid){
    if(_s[moveid]._red==_s[killid]._red){
        //��ѡ��
        _selectid=killid;
        update();
        return false;
    }
    switch (_s[moveid]._type) {
    case Stone::JIANG:
        return canMove1(moveid, row, col, killid);
        break;
    case Stone::SHI:
        return canMove2(moveid, row, col, killid);
        break;
    case Stone::XIANG:
        return canMove3(moveid, row, col, killid);
        break;
    case Stone::CHE:
        return canMove4(moveid, row, col, killid);
        break;
    case Stone::MA:
        return canMove5(moveid, row, col, killid);
        break;
    case Stone::PAO:
        return canMove6(moveid, row, col, killid);
        break;
    case Stone::BING:
        return canMove7(moveid, row, col, killid);
        break;
    }
    return true;
}

void Board::mouseReleaseEvent(QMouseEvent*ev){
    QPoint pt=ev->pos();
    //��ptת��Ϊ���������ֵ���ж��������ֵ������û������
    //����� ѡ��
    int row;
    int col;
    bool bRet=getRowCol(pt,row,col);
    //�㵽����������
    if(bRet==false)
        return;

    int i;
    int clickid=-1;
    for(i=0;i!=32;++i)
        if(_s[i]._row==row&&_s[i]._col==col&&_s[i]._dead==false)
            break;
    if(i<32)
        clickid=i;//��õ�����ӵı��


    if(_selectid==-1){
        if(clickid!=-1){
            if(_bRedTurn==_s[clickid]._red){
                _selectid=clickid;
                update();//���µ���paintEvent()��
            }
        }
    }else if(canMove(_selectid,row,col,clickid)){
        _s[_selectid]._row=row;
        _s[_selectid]._col=col;
        //����ĵط���������� ��Ե�
        if(clickid!=-1)
            _s[clickid]._dead=true;
        _selectid=-1;
        _bRedTurn=!_bRedTurn;
        update();//�ػ�����
    }


}
