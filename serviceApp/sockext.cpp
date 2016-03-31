#include "sockext.h"
#include <qlocalsocket.h>
SockExt::SockExt(QLocalSocket *socket, QObject *parent)
{
    this->socket = socket;
    type=0;
}

SockExt::~SockExt()
{

}


