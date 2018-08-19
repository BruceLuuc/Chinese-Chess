#include<QApplication>
#include<QTextCodec>
#include"SingleGame.h"

//Kit Qt4.8.7
int main(int argc,char*argv[]){
    //�������н��������������
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));

    QApplication app(argc,argv);
    SingleGame board;
    board.setWindowTitle("�й�����");
    board.show();
    return app.exec();
}
