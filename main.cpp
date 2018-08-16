#include<QApplication>
#include"Board.h"
#include<QTextCodec>


//Kit 4.8.7
int main(int argc,char*argv[]){
    //以下三行解决汉字乱码问题
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));


    QApplication app(argc,argv);
    Board board;
    board.setWindowTitle("中国象棋");
    board.show();
    return app.exec();
}
