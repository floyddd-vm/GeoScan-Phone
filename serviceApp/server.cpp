/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QtNetwork>

#include <stdlib.h>

#include "server.h"

#include <qlocalserver.h>

#include <qtelephonynamespace.h>
#include <qatchat.h>

Server::Server(QWidget *parent)
    : QDialog(parent)
{
    statusLabel = new QLabel;
    statusLabel->setWordWrap(true);
    quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);

    writeButton = new QPushButton(tr("write"));
    writeButton->setAutoDefault(false);
    modem = new GsmModem();
    modem->init("COM3",115200);
    connect(modem, SIGNAL(initialized(bool)), this, SLOT(onInitialized(bool)));
    //connect(modem, SIGNAL(operatorName(QString)), this, SLOT(onOperatorName(QString)));
    //connect(modem, SIGNAL(signalLevels(int,int)), this, SLOT(onSignalLevel(int,int)));

    //--------------------------
    server = new QLocalServer(this);
    if (!server->listen("fortune")) {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(server->errorString()));
        close();
        return;
    }

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(writeButton, SIGNAL(clicked()), this, SLOT(sendCmd()));
    connect(server, SIGNAL(newConnection()), this, SLOT(sockInit()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(writeButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Fortune Server"));


}

void Server::onInitialized(bool initialized)
{
    if (initialized) {
        qDebug() << "Modem is initialized";

        smsObj = new GsmSMS(modem);

        connect(smsObj, SIGNAL(SmsRecieved(QString, QString)),this, SLOT(onSmsRecieved(QString, QString)));

        //Обрабтка события входящего звонка
        modem->primaryAtChat()->registerNotificationType
           ( "+CLIP:", this, SLOT(callEvent(QString)) );
        //Событие завершенния вызова
        //modem->primaryAtChat()->registerNotificationType
        //   ( "MISSED_CALL", this, SLOT(callDone()));
    /*  Здесь обработка входящих SMS    */

    } else {
        qDebug() << "Failed to initialize modem";
        qApp->exit(-1);
    }
}


void Server::onSmsRecieved(QString smsText, QString sender)
{
    //Todo: старт приложения смс
    qDebug() << "Start smsApp";
    QProcess process;
    process.startDetached("C:\\Users\\floyd\\Documents\\qt\\phone\\build-smsApp-Desktop_Qt_5_6_0_MinGW_32bit-Debug\\debug\\smsApp.exe");
    qDebug() << process.errorString();
}

void Server::sockInit()
{
    qDebug() << "Somebody connected";
    blockSize = 0;
    //QLocalSocket *ls = ;
    //SockExt se;
    //se.socket = ls;
    SockExt *se = new SockExt(server->nextPendingConnection(), this);
    //sockets.append(se);
    sockets << se;
    //delete se;
    qDebug() <<"Socket: " << se->socket;
    connect(sockets.last()->socket, SIGNAL(readyRead()), this, SLOT(sockRead()));
    /* TODO: Создание нескольких сокетов для Call и SMS, назначение слотов */
    int initialized = 1;
    sockWrite(sockets.last()->socket, "WHO");
}

void Server::sockWrite(QLocalSocket *socket, QString mes)
{
    qDebug() << "Write to socket: " << mes;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << mes;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    connect(socket, SIGNAL(disconnected()),
            socket, SLOT(deleteLater()));

    socket->write(block);
    socket->flush();
    //socket->disconnectFromServer();
}

/* Получение данных из сокета  */
void Server::sockRead()
{
    QLocalSocket *se = qobject_cast<QLocalSocket*>(QObject::sender());
    QDataStream in(se);
    in.setVersion(QDataStream::Qt_4_0);
    blockSize = 0;
    if (blockSize == 0) {
        if (se->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }

    if (in.atEnd())
        return;

    QString ATcmd;
    in >> ATcmd;
    qDebug() << "Read from socket: " << ATcmd;
    if(ATcmd.indexOf("WHO:") != -1)
    {
        for(int i=0;i<sockets.count(); i++)
        {
            qDebug() << "socD: " << sockets.at(i)->socket->socketDescriptor() << "socD: " << se->socketDescriptor();
            if(sockets.at(i)->socket->socketDescriptor() == se->socketDescriptor())
            {
                sockets[i]->type = ATcmd.mid(4).toInt();
            }
        }
        return;
    }
    if(ATcmd.indexOf("EXIT") != -1)
    {
        for(int i=0;i<sockets.count(); i++)
        {
            if(sockets.at(i)->socket->socketDescriptor() == se->socketDescriptor())
            {
                sockets.takeAt(i);
                isCallApp = false;
                qDebug() << "Call exit";
            }
        }
    }
    else
        modem->primaryAtChat()->send(ATcmd);
}


void Server::callEvent(QString number)
{
    //  TODO: запуск callApp и проверка на запущенность
    //int i = sockets.indexOf("1");
    if(!isCallApp)
    {
        QString path = "C:\\handset.exe -" + number;
        qDebug() << path;
        QProcess process;
        process.startDetached(path);
         //запуск callApp
        qDebug() << process.errorString();
        /*
        while(process.state() != QProcess::Running)
        {
            qDebug() << process.state();
            Sleep(500);
        }
        */
        isCallApp = true;
        //sockWrite(callSock, "RING:" + number);
        return;
    }
        int start = number.indexOf("\"")+1;
        int end = number.indexOf("\"",start);
        qDebug() << start<<"  "<<end;
        qDebug() << "Call event: " ;
        for(int i=0;i<sockets.count(); i++)
        {
            qDebug() << "soc: " << sockets.at(i)->socket << "type : " << sockets.at(i)->type;
            if(sockets.at(i)->type == 1)
            {
                sockWrite(sockets.at(i)->socket, "RING:" + number.mid(start,end-start));
            }
        }
}

void Server::sendCmd()
{
    QString ATcmd = "123456";
    callEvent("123456789");
    /*
    for( int i=0; i<sockets.count(); ++i )
    {
        sockWrite(sockets.at(i)->socket, "RING:" + ATcmd);
    }
    */

}


