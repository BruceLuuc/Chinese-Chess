#include "SingleGame.h"


void SingleGame::click(int id,int row,int col){

    if(!this->_bRedTurn)
        return;
    Board::click(id,row,col);
    //�������� �����ߺ���
    if(!this->_bRedTurn)
        computerMove();
}

//1.��������Щ���������
//2.������һ��
//3.�����ߵĽ��
//4.ȡ��õĽ��
void SingleGame::computerMove(){

}
