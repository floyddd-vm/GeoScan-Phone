#include "smsmain.h"

SmsMain::SmsMain(QQmlApplicationEngine *_view)
{
      db = new DataBase();
      view = _view;
      socket = new QLocalSocket();

      socket->abort();
      socket->connectToServer("fortune");

      blockSize = 0;
      connect(socket, SIGNAL(readyRead()), this, SLOT(sockRead()));
      connect(socket, SIGNAL(error(QLocalSocket::LocalSocketError)),
              this, SLOT(displayError(QLocalSocket::LocalSocketError)));

}
QList<QObject*> SmsMain::getDialogList()
{

      QSqlQuery data; // - хранит результаты выполнения запроса Select.
      QString tFields;

      //tFields = "SenderID, RecipientID, Date, Time, Text";
      tFields = "SenderID, RecipientID, Text, Time";

      data = db->getDialog();

      QList<QObject*> dataList;
                  //QStringList dataList;
      QSqlQuery query;

      while (data.next()) {

          QString contact;

          //Проверяем исодящее или входящее сообщение

          //Достаем информацию о собеседнике
          query = db->findInfoByParams(T_CONTACTS, "ID", data.record().value(1).toString());
          query.next();


          if(query.record().value(1).toString() == " ")
              contact = query.record().value(3).toString();
          else
              contact = query.record().value(1).toString() +" "+ query.record().value(2).toString();

          dataList.append(new DialogObject(data.record().value(1).toLongLong(),
                                           contact,
                                           data.record().value(2).toLongLong(),
                                           data.record().value(3).toString(),
                                           data.record().value(4).toString()));
      }



      return dataList;
}

void SmsMain::onSendMsg(QString id, QString msg)
{

    qDebug()<<currentNumber<<","<<msg;
    sockSend("SMS:"+currentNumber+","+msg);
}


void SmsMain::onChatChoice(QString id, QString contact)
{
    QList<QObject*> dataList;
    QSqlQuery data;


    data = db->findInfoByParams(T_CONTACTS, "ID", id);
    data.next();
    currentNumber = data.record().value(3).toString();

    //Выборка всех сообщений по данному контакту
    data = db->sortFindInfoByParams(T_MESSAGES, "ContactID", id);
    while (data.next()) {
        dataList.append(new DialogObject(data.record().value(0).toLongLong(),
                                         data.record().value(1).toString(),
                                         data.record().value(2).toLongLong(),
                                         data.record().value(3).toString(),
                                         data.record().value(4).toString()));
    }

    QQmlContext *ctxt = view->rootContext();
    ctxt->setContextProperty("chatContact", QVariant::fromValue(dataList));


    //Смена загаловка
    QList<QObject*> qml = view->rootObjects();
    QObject *Title = qml.first()->findChild<QObject*>("title");
    Title->setProperty("text",contact);

}


void SmsMain::sockSend(QString mes)
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

    socket->write(block);
    socket->flush();
    //sock->disconnectFromServer();
}

void SmsMain::sockRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);
    blockSize = 0;
    if (blockSize == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }

    if (in.atEnd())
        return;

    QString ATcmd;
    in >> ATcmd;

    if(ATcmd.indexOf("WHO") != -1)
        sockSend("WHO:2");
 /*
    if(ATcmd.indexOf("RING:") != -1)
        emit incomingCall(ATcmd.mid(5));

    else if(ATcmd.indexOf("INIT:") != -1)
        emit initialized(ATcmd.mid(5).toInt());
*/
}
