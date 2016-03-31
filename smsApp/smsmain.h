#ifndef SMSMAIN_H
#define SMSMAIN_H
#include <QString>
#include <qlocalsocket.h>
#include <QObject>
#include <QDebug>
#include "database.h"
#include "dialogobject.h"
#include <qqmlcontext.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include <QQmlApplicationEngine>

class QLocalSocket;

class SmsMain: public QObject
{
    Q_OBJECT
public:
    SmsMain(QQmlApplicationEngine *_view);

    QQmlApplicationEngine *view;
    DataBase *db;
    QString currentNumber;

    quint16 blockSize;
public slots:
    void onChatChoice(QString phone, QString contact);
    void onSendMsg(QString id, QString msg);
    QList<QObject*> getDialogList();

    void sockSend(QString);
    void sockRead();
private:
    QLocalSocket *socket;

};

#endif // SMSMAIN_H
