#include "SingleGame.h"
#include<QTimer>

void SingleGame::click(int id,int row,int col){

    if(!this->_bRedTurn)
        return;
    Board::click(id,row,col);
    //�������� �����ߺ���  ���ø���ʱ�� ��ˢ�����������Ĳ���  ���õ�������˼��
    if(!this->_bRedTurn)
        QTimer::singleShot(100,this,SLOT(computerMove()));
}
void SingleGame::computerMove(){
    Step*step=getBestMove();
    moveStone(step->_moveid,step->_killid,step->_rowTo,step->_colTo);
    delete step;
    update();
}
//1.��������Щ���������,��������
//2.������һ��
//3.�����ߵĽ��
//4.ȡ��õĽ��
Step* SingleGame::getBestMove(){
    //��1��
    QVector<Step*>steps;
    getAllPossibleMove(steps);
    //��2��
    int maxScore=INT_MIN;
    Step* ret=NULL;
    while(steps.count()){
        Step*step=steps.back();
        steps.pop_back();
        fakeMove(step);//����һ��
        int score=getMinScore(_level-1,maxScore);
        //int score=-AlphaBeta(_level-1,-maxScore);
        unfakeMove(step);//��ԭ
        if(score>maxScore){
            maxScore=score;
            if(ret)delete ret;
            ret=step;
        }else{
            delete step;
        }
    }
    //��4��
    return ret;

}

void SingleGame::getAllPossibleMove(QVector<Step*>&steps){

    int min=16;
    int max=32;
    if(this->_bRedTurn){
        min=0;
        max=16;
    }
    for(int i=min;i!=max;++i){
        //ȥ��������
        if(_s[i]._dead)
            continue;
        for(int row=0;row!=10;++row)
            for(int col=0;col!=9;++col){
                int killid=this->getStoneId(row,col);
                if(sameColor(killid,i))continue;
                if(canMove(i,row,col,killid))
                    saveStep(i,killid,row,col,steps);//������ ����һ��
            }
    }
}


void SingleGame::fakeMove(Step*step){
    killStone(step->_killid);
    moveStone(step->_moveid,step->_rowTo,step->_colTo);
}
void SingleGame::unfakeMove(Step*step){
    reliveStone(step->_killid);
    moveStone(step->_moveid,step->_rowFrom,step->_colFrom);
}
//���۾����
int SingleGame::calcScore(){
    int redTotalScore=0;
    int blackTotalScore=0;
    //enum TYPE{CHE,MA,PAO,BING,JIANG,SHI,XIANG};
    static int chessScore[]={100,50,50,20,1500,10,10};
    //������ܷ�-������ܷ�
    for(int i=0;i!=16;++i){
        if(_s[i]._dead)continue;
        redTotalScore+=chessScore[_s[i]._type];
    }
    for(int i=16;i!=32;++i){
        if(_s[i]._dead)continue;
        blackTotalScore+=chessScore[_s[i]._type];
    }

    return blackTotalScore-redTotalScore;
}


int SingleGame::getMaxScore(int level,int curMinScore){
    if(level==0)return calcScore();
    QVector<Step*>steps;
    getAllPossibleMove(steps);
    int maxScore=INT_MIN;
    while(steps.count()){
        Step*step=steps.back();
        steps.pop_back();
        fakeMove(step);
        int score=getMinScore(level-1,maxScore);
        unfakeMove(step);
        delete step;
        if(score>=curMinScore){
            while(steps.count()){
                Step*step=steps.back();
                steps.pop_back();
                delete step;
            }
            return score;
        }

        if(score>maxScore)
            maxScore=score;

    }
    return maxScore;
}

int SingleGame::getMinScore(int level,int curMaxScore){
    if(level==0)return calcScore();
    QVector<Step*>steps;
    getAllPossibleMove(steps);//�����PossibleMove
    int minScore=INT_MAX;
    while(steps.count()){
        Step*step=steps.back();
        steps.pop_back();
        fakeMove(step);
        int score=getMaxScore(level-1,minScore);
        unfakeMove(step);
        delete step;//�ͷ��ڴ�
        if(score<=curMaxScore){
            //�ͷű���֦���ڴ�
            while(steps.count()){
                Step*step=steps.back();
                steps.pop_back();
                delete step;
            }
            return score;
        }

        if(score<minScore)
            minScore=score;
    }
    return minScore;
}
//����AlphaBeta��֦
int SingleGame::AlphaBeta(int level,int preScore){
    if(level==0)return calcScore();
    QVector<Step*>steps;
    getAllPossibleMove(steps);
    int maxScore=INT_MIN;
    while(steps.count()){
        Step*step=steps.back();
        steps.pop_back();
        fakeMove(step);
        int score=-AlphaBeta(level-1,-maxScore);
        unfakeMove(step);
        delete step;
        if(score>=preScore){
            while(steps.count()){
                Step*step=steps.back();
                steps.pop_back();
                delete step;
            }
            return score;
        }

        if(score>maxScore)
            maxScore=score;
    }
    return maxScore;
}
