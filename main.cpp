#include<QApplication>
#include<QTextCodec>
#include"SingleGame.h"

//Kit Qt4.8.7
int main(int argc,char*argv[]){
    //以下三行解决汉字乱码问题
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));

    QApplication app(argc,argv);
    Board *board;
    SingleGame singleGame;
    board=&singleGame;//虚函数动态联编
    board->setWindowTitle("中国象棋");
    board->show();
    return app.exec();
}
