#ifndef NETGAME_H
#define NETGAME_H
#include"Board.h"
#include<QTcpServer>
#include <QTcpSocket>

/*
 * ���ĸ�ʽ����
 * 1.��ʼ��    �����ֽ�: ��һ���ֽڹ̶���1���ڶ����ֽ���1������0��1��ʾ���շ��ߺ��죬0��ʾ�ߺ���
 * 2.�����   �ĸ��ֽ�: ��һ���ֽڹ̶���2���ڶ����ֽ���row���������ֽ���col�����ĸ��ֽ��ǵ��������id
 * 3.����      һ���ֽ�
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
