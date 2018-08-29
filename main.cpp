#include<QApplication>
#include<QTextCodec>
#include"SingleGame.h"
#include "NetGame.h"
#include <QMessageBox>

//Kit Qt4.8.7
int main(int argc,char*argv[]){
    //�������н��������������
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));

    QApplication app(argc,argv);


    Board *board;
    SingleGame singleGame;
    board=&singleGame;//�麯����̬����
    board->setWindowTitle("�й�����");
    board->show();


//    QMessageBox::StandardButton ret;
//    ret = QMessageBox::information(NULL, "��������ͻ���", "��Ϊ������������",QMessageBox::Yes | QMessageBox::No);
//    bool bServer = false;
//    if(ret == QMessageBox::Yes)
//         bServer = true;
//    NetGame netGame(bServer);

//    netGame.setWindowTitle("�й�����");
//    netGame.show();


    return app.exec();
}
