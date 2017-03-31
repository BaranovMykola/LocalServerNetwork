#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>

class QLocalServer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void slotNewConnection();
    void slotRead();
    void slotWrite();
private:
    Ui::MainWindow *ui;
    QLocalServer* mServer;
    QLocalSocket* mClient;
};

#endif // MAINWINDOW_H
