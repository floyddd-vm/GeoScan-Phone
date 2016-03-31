#include "callmain.h"

CallMain::CallMain()
{
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
    db = new DataBase();
}

CallMain::~CallMain()
{

}

void CallMain::onEndCall()
{
    callObj->endCall();
    callObj->exit();
    emit appQuit();
    //qDebug() << "типа закрылось";
    //QObject *phoneField = qml->findChild<QObject*>("phone");
    //phoneField->setProperty("text",QVariant(phoneNum.remove(0, 1)));
}

void CallMain::onDeclined()
{
    callObj->decline();
    //Sleep(700);
    // TODO: задержка закрытия
    callObj->exit();
    emit appQuit();
}

void CallMain::addContact(QString name, QString sname, QString number)
{
    qDebug() << "работает";
    QVariantList params;
    params << name
          << sname
          << number;
    //db->insertIntoTable(T_CONTACTS,params);
    qDebug() << "успех";
}

void CallMain::addCallRec(QString name, QString sname, QString number)
{
    qDebug() << "addCallRec";

    QVariantList params;
    params << name
          << sname
          << number;
    //db->insertIntoTable(T_CONTACTS,params);
    qDebug() << "успех";
}


