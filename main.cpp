#include<QApplication>
#include<QTextCodec>
#include"Board.h"

//Kit Qt4.8.7
int main(int argc,char*argv[]){
    //�������н��������������
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));


    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));

    QApplication app(argc,argv);
    Board board;
    board.setWindowTitle("�й�����");
    board.show();
    return app.exec();
}
