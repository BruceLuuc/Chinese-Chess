#include "SingleGame.h"


void SingleGame::click(int id,int row,int col){

    if(!this->_bRedTurn)
        return;
    Board::click(id,row,col);
    //�������� �����ߺ���
    if(!this->_bRedTurn)
        computerMove();
}

//1.��������Щ���������,��������
//2.������һ��
//3.�����ߵĽ��
//4.ȡ��õĽ��
void SingleGame::computerMove(){
    //��һ��
    QVector<Step*>steps;
    getAllPossibleMove(steps);

}

void SingleGame::getAllPossibleMove(QVector<Step*>&steps){
    //�������к��忴���߷�
    for(int i=16;i!=32;++i){
        for(int row=0;row!=10;++row){
            for(int col=0;col!=9;++col){
                int killid=this->getStoneId(row,col);
                if(sameColor(killid,i))continue;
                if(canMove(i,row,col,killid)){
                    //������ ����һ��
                    saveStep(i,killid,row,col,steps);
                }
            }
        }
    }
}
