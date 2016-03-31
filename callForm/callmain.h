#ifndef CALLMAIN_H
#define CALLMAIN_H

#include <QObject>
#include "gsmcall.h"
#include "database.h"
#include <qlocalsocket.h>

class CallMain : public QObject
{
    Q_OBJECT
public:
    explicit CallMain();

    ~CallMain();
    GSMCall *callObj;
    QLocalSocket *socket;
    DataBase *db;
signals:
    void appQuit();
public slots:
    void onEndCall();
    void addContact(QString name, QString sname, QString number);
    void onDeclined();
    void addCallRec(QString name, QString sname, QString number);
private:

};

#endif // CALLMAIN_H
