#include<QApplication>
#include<QTextCodec>
#include"SingleGame.h"
#include "NetGame.h"
#include <QMessageBox>

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


//    QMessageBox::StandardButton ret;
//    ret = QMessageBox::information(NULL, "服务器或客户机", "作为服务器启动？",QMessageBox::Yes | QMessageBox::No);
//    bool bServer = false;
//    if(ret == QMessageBox::Yes)
//         bServer = true;
//    NetGame netGame(bServer);

//    netGame.setWindowTitle("中国象棋");
//    netGame.show();


    return app.exec();
}
