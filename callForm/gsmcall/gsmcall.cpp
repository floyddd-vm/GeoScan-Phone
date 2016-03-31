#include "gsmcall.h"
#include <QRegExp>

#include <QtNetwork>

#include <stdlib.h>

GSMCall::GSMCall(QLocalSocket *socket, QObject *parent):
    QObject(parent)
{
   this->sock = socket;
}

GSMCall::~GSMCall()
{
    delete this;
}

void GSMCall::call(QString number)
{
     sockSend("ATD"+number+";");
}

void GSMCall::accept()
{
     sockSend("ATA");
     qDebug() << "Accepted";
}

void GSMCall::decline()
{
     sockSend("AT+CHUP");
     qDebug() << "Declined";
}

void GSMCall::endCall()
{
     sockSend("ATH0");
     qDebug() << "endCall";
}

void GSMCall::exit()
{
     sockSend("EXIT");
     qDebug() << "exit";
}

void GSMCall::missedCall()
{
     sockSend("EXIT");
     qDebug() << "missedCall. App will exit";
}

void GSMCall::sockSend(QString mes)
{
    //qDebug() << "Write to socket: " << mes;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << mes;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    //connect(sock, SIGNAL(disconnected()), sock, SLOT(deleteLater()));

    sock->write(block);
    sock->flush();
    //sock->disconnectFromServer();
}

void GSMCall::sockRead()
{
    QString init = "INIT";
    QString ring = "RING";
    QDataStream in(sock);
    in.setVersion(QDataStream::Qt_4_0);
    blockSize = 0;
    if (blockSize == 0) {
        if (sock->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }

    if (in.atEnd())
        return;

    QString ATcmd;
    in >> ATcmd;
//    QRegExp re(,["\\s\\S]*$");
//    if (re.indexIn(ATcmd.content(), 0) >= 0)
//    {
//        operator_ = re.cap(1);
//        emit operatorName(operator_);
//    }
    //qDebug() << "Read from socket: " << ATcmd;
    if(ATcmd.indexOf("WHO") != -1)
        sockSend("WHO:1");
    //if(ATcmd.indexOf("MISSED") != -1);
        //sockSend("WHO:1");
    if(ATcmd.indexOf("RING:") != -1)
        emit incomingCall(ATcmd.mid(5));

    else if(ATcmd.indexOf("INIT:") != -1)
        emit initialized(ATcmd.mid(5).toInt());
    //else if(ATcmd.at(0) == "INIT")
      //  emit

    //modem->primaryAtChat()->send(ATcmd);
}

