#include "localclient.h"

#include <QtNetwork/QLocalSocket>
#include <QDataStream>
#include <QDebug>

LocalClient::LocalClient()
{
    mLocalClient = new QLocalSocket(this);
    mLocalClient->connectToServer("KuzyaServer");
    connect(mLocalClient, SIGNAL(readyRead()), this, SLOT(slotReadCommands()), Qt::UniqueConnection);
//    mLocalClient->waitForReadyRead(1000);
    //    qDebug() << mLocalClient->readAll();
}

void LocalClient::write(QByteArray message)
{
    mLocalClient->write(message);
    mLocalClient->flush();
}

void LocalClient::slotReadCommands()
{
    qDebug() << mLocalClient->readAll();
}
