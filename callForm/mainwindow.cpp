#include "mainwindow.h"

#include <QDebug>
#include <QtNetwork>
//#include <qtelephonynamespace.h>
#include <QLocalSocket>

class MainWindow : public QDeclarativeView

{
    /*
       socket = new QLocalSocket();
       //int a = socket->setSocketDescriptor(0xfafafa, QLocalSocket::UnconnectedState, QIODevice::ReadWrite );
       //quintptr sd =  socket->socketDescriptor();
       //a = 25;
       socket->abort();
       socket->connectToServer("fortune");
       callObj = new GSMCall(socket);
        callObj->blockSize = 0;
       connect(socket, SIGNAL(readyRead()), callObj, SLOT(sockRead()));
       connect(socket, SIGNAL(error(QLocalSocket::LocalSocketError)),
               this, SLOT(displayError(QLocalSocket::LocalSocketError)));

       //connect(callObj, SIGNAL(initialized(bool)),this, SLOT(onInitialized(bool)));
       connect(callObj, SIGNAL(incomingCall(QString)),this, SLOT(callEvent(QString)));

       //connect(callObj, SIGNAL(callDone()),this, SLOT(callDone()));

       ui->setupUi(this);

       //Делаем все невидимым
          ui->label->setVisible(false);
          ui->btnAccept->setVisible(false);
          ui->btnDecline->setVisible(false);
          */
}
MainWindow::~MainWindow()
{
    delete ui;
}


