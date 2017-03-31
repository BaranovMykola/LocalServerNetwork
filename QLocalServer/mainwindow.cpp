#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>
#include <QByteArray>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mServer = new QLocalServer(this);
    if(!mServer->listen("KuzyaServer"))
    {
        ui->output->appendPlainText(tr("Unable to start this server: %1").arg(mServer->errorString()));
       // return;
    }
    else
    {
        ui->output->appendPlainText("Server is running");
    }
    connect(mServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()), Qt::UniqueConnection);
    connect(ui->commandLine, SIGNAL(returnPressed()), this, SLOT(slotWrite()), Qt::UniqueConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotNewConnection()
{
    QLocalSocket *localSocket = mServer->nextPendingConnection();
//    connect(localSocket, SIGNAL(disconnected()), localSocket, SLOT(deleteLater()));
    QString message = "Heelo, world! (via Server)";
    localSocket->write("Heelo, world! (via Server)");
    ui->output->appendPlainText(tr("Trying to write %1").arg(message));
    bool written = localSocket->flush();
    ui->output->appendPlainText(tr("Message was written ").arg(written ? "succsesfully" : "with error"));
    //localSocket->disconnectFromServer();
    ui->commandLine->setEnabled(true);
    mClient = localSocket;
}

void MainWindow::slotRead()
{
    //    ui->output(tr("Read from client: %1").arg(mServer->));
}

void MainWindow::slotWrite()
{
    mClient->write(ui->commandLine->text().toStdString().c_str());
    mClient->flush();
    ui->commandLine->clear();
}
