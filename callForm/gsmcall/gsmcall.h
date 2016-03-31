#ifndef GSMCALL_H
#define GSMCALL_H
#include <qlocalsocket.h>
#include <QObject>

class QLocalSocket;

class GSMCall: public QObject
{
    Q_OBJECT
public:
    GSMCall(QLocalSocket *socket, QObject *parent = 0);
    ~GSMCall();
quint16 blockSize;
signals:
    void incomingCall(QString);
    void initialized(bool);
public slots:
    void call(QString);
    void endCall();
    void accept();
    void decline();

    void sockSend(QString);
    void sockRead();
    void exit();
    void missedCall();
private:
    QLocalSocket *sock;

};

#endif // GSMCALL_H
