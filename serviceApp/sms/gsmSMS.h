#ifndef GsmSMS_H
#define GsmSMS_H

#include <QObject>
#include "database.h"

class GsmModem;
class GsmSmsReader;
class GsmSmsSender;

class GsmSMS : public QObject
{
    Q_OBJECT
public:
    explicit GsmSMS(GsmModem *mdm, QObject *parent = 0);

signals:
    void SmsRecieved(QString smsText, QString sender);
    void smsSenderSign(const QString &id, const int &code);
public slots:
    void sendSMS(QString mes, QString phone);
    void onMessageCount(int count);
    void onStartSendingSms(const QString &id);
    void onFinished(const QString &id, const int &code);

private:
    void readSmsMessages(const bool deleteSmsAfterRead = false);

public:
    GsmModem *m_modem;
    GsmSmsReader *m_reader;
    GsmSmsSender *m_sender;

    DataBase *db;
};

#endif // GsmSMS_H
