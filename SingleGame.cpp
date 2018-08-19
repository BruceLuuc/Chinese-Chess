#include "SingleGame.h"


void SingleGame::click(int id,int row,int col){

    if(!this->_bRedTurn)
        return;
    Board::click(id,row,col);
    //红棋走完 立马走黑棋
    if(!this->_bRedTurn)
        computerMove();
}

//1.看看有哪些步骤可以走
//2.试着走一下
//3.评估走的结果
//4.取最好的结果
void SingleGame::computerMove(){

}
