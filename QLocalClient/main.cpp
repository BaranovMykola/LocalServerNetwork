#include <QCoreApplication>

#include <QDebug>
#include <string>
#include <iostream>
#include <QtNetwork/QLocalSocket>
#include <QTextStream>

#include "localclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    QLocalSocket* localSocket= new QLocalSocket();
//    localSocket->connectToServer("KuzyaServer");
    LocalClient client;
    QByteArray message;
    QTextStream qtin(stdin);
//    QDataStream qtin;
    /*
    do
    {
        qtin>> message;
    }
    while(message != "exit");*/
    a.exec();
    return 0;
}
