#include<QApplication>
#include"Board.h"
#include<QTextCodec>


//Kit 4.8.7
int main(int argc,char*argv[]){
    //�������н��������������
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));


    QApplication app(argc,argv);
    Board board;
    board.setWindowTitle("�й�����");
    board.show();
    return app.exec();
}
