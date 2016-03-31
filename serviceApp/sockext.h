#ifndef SOCKEXT_H
#define SOCKEXT_H

#endif // SOCKEXT_H
#include <qlocalsocket.h>
class SockExt : public QObject
{
    Q_OBJECT
public:
    SockExt(QLocalSocket *socket, QObject *parent = 0);
    ~SockExt();

    QLocalSocket *socket;
    int type;
};
