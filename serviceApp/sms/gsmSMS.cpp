#include "gsmSMS.h"
#include "gsmmodem.h"
#include "gsmsmsreader.hpp"
#include "gsmsmssender.hpp"
#include "qtelephonynamespace.h"
#include <QDebug>
#include <QCoreApplication>
#include <QUuid>

GsmSMS::GsmSMS(GsmModem *modem, QObject *parent) :
    QObject(parent),
    m_reader(new GsmSmsReader(modem, this)),
    m_sender(new GsmSmsSender(modem, this))
{
    m_modem = modem;
    db = new DataBase;
    connect(m_reader, SIGNAL(messageCount(int)), this, SLOT(onMessageCount(int)));
    connect(m_sender, SIGNAL(startSendingSms(QString)), this, SLOT(onStartSendingSms(QString)));
    connect(m_sender, SIGNAL(finished(QString,int)), this, SLOT(onFinished(QString,int)));
}

void GsmSMS::sendSMS(QString mes, QString phone)
{
        //m_reader->check();
        qDebug() << "Send sms";
        qDebug() << phone;
        qDebug() << mes;

        QSMSMessage sms;
        sms.setText(mes);

        sms.setRecipient(phone);
        sms.setStatusReportRequested(true);
        m_sender->send(QUuid::createUuid().toString(), sms);
}


void GsmSMS::onMessageCount(int count)
{
    Q_UNUSED(count)
    readSmsMessages(true);
}

void GsmSMS::onStartSendingSms(const QString &id)
{
    qDebug() << QString("Start sending sms whit id %0").arg(id);
}

void GsmSMS::onFinished(const QString &id, const int &code)
{
    qDebug() << "Send sms finished";
    emit smsSenderSign(id,code);
}

void GsmSMS::readSmsMessages(const bool deleteSmsAfterRead)
{
    qDebug() << "Sms reading";
    QStringList smsIdList;
    for (int i = 0; i < m_reader->count(); ++i) {
        const QSMSTaggedMessage *message = m_reader->at(i);
        if (message) {

            QVariantList params;
            params << 7
                   << 3
                   << message->message.timestamp()
                   << message->message.timestamp().time()
                   << message->message.text();

            db->insertIntoTable(T_MESSAGES,params);
            qDebug() << message->message.timestamp().date();
            qDebug() << message->message.timestamp().time();
            qDebug() << QString("Message '%0' from '%1' received")
                        .arg(message->message.text())
                        .arg(message->message.sender());
            if (deleteSmsAfterRead)
                smsIdList << message->identifier;
            emit SmsRecieved(message->message.text(), message->message.sender());
        }
    }
    for (const QString &id: smsIdList) {
        m_reader->deleteMessage(id);
    }
}
