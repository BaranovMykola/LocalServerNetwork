#ifndef LOCALCLIENT_H
#define LOCALCLIENT_H

#include <QObject>
#include <QByteArray>

class QLocalSocket;

class LocalClient : QObject
{
    Q_OBJECT
public:
    LocalClient();
    void write(QByteArray message);
private slots:
    void slotReadCommands();
private:
    QLocalSocket* mLocalClient;
};

#endif // LOCALCLIENT_H
