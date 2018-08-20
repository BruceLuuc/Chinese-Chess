#ifndef NETGAME_H
#define NETGAME_H
#include"Board.h"
#include<QTcpServer>
#include <QTcpSocket>

/*
 * 报文格式定义
 * 1.初始化    两个字节: 第一个字节固定是1，第二个字节是1，或者0，1表示接收方走红旗，0表示走黑棋
 * 2.鼠标点击   四个字节: 第一个字节固定是2，第二个字节是row，第三个字节是col，第四个字节是点击的棋子id
 * 3.悔棋      一个字节
 *
*/

class NetGame : public Board
{
    Q_OBJECT
public:
    explicit NetGame(bool server, QWidget *parent = 0);
    ~NetGame(){}


    QTcpServer* _server;
    QTcpSocket* _socket;

    void click(int id, int row, int col);

signals:

public slots:
    void slotNewConnection();
    void slotDataArrive();
};

#endif // NETGAME_H
