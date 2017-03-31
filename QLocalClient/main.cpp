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
    LocalClient client;
    QByteArray message;
    QTextStream qtin(stdin);

    do
    {
        message.clear();
        message.append(qtin.readLine());
        client.write(message);
    }
    while(message != "exit");
    a.exec();
    return 0;
}
