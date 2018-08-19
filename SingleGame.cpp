#include "SingleGame.h"


void SingleGame::click(int id,int row,int col){

    if(!this->_bRedTurn)
        return;
    Board::click(id,row,col);
    //红棋走完 立马走黑棋
    if(!this->_bRedTurn)
        computerMove();
}

//1.看看有哪些步骤可以走,并存起来
//2.试着走一下
//3.评估走的结果
//4.取最好的结果
void SingleGame::computerMove(){
    //第一步
    QVector<Step*>steps;
    getAllPossibleMove(steps);

}

void SingleGame::getAllPossibleMove(QVector<Step*>&steps){
    //遍历所有黑棋看看走法
    for(int i=16;i!=32;++i){
        for(int row=0;row!=10;++row){
            for(int col=0;col!=9;++col){
                int killid=this->getStoneId(row,col);
                if(sameColor(killid,i))continue;
                if(canMove(i,row,col,killid)){
                    //可以走 保存一下
                    saveStep(i,killid,row,col,steps);
                }
            }
        }
    }
}
