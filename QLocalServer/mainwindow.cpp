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
    connect(localSocket, SIGNAL(readyRead()), this, SLOT(slotRead()), Qt::UniqueConnection);
    ui->commandLine->setEnabled(true);
}

void MainWindow::slotRead()
{
    QLocalSocket* senderSocket = (QLocalSocket*)sender();
    ui->output->appendPlainText(senderSocket->readAll());
}

void MainWindow::slotWrite()
{
    mClient->write(ui->commandLine->text().toStdString().c_str());
    mClient->flush();
    ui->commandLine->clear();
}
