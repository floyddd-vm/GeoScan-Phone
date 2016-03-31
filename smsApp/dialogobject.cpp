#include <QDebug>
#include "dialogobject.h"

DialogObject::DialogObject(QObject *parent)
    : QObject(parent)
{
}

DialogObject::DialogObject(const qlonglong &id, const QString &contact, const qlonglong &status, const QString &dateTime, const QString &message, QObject *parent)
    : QObject(parent), _id(id), _contact(contact), _status(status), _dateTime(dateTime),  _message(message)
{
}

qlonglong DialogObject::id() const
{
    return _id;
}

void DialogObject::setId(qlonglong &id)
{
    if (id != _id) {
        _id = id;
        emit idChanged();
    }
}

qlonglong DialogObject::status() const
{
    return _status;
}

void DialogObject::setStatus(const qlonglong &status)
{
    if (status != _status) {
        _status = status;
        emit statusChanged();
    }
}

QString DialogObject::contact() const
{
    return _contact;
}

void DialogObject::setContact(const QString &contact)
{
    if (contact != _contact) {
        _contact = contact;
        emit contactChanged();
    }
}

QString DialogObject::message() const
{
    return _message;
}

void DialogObject::setMessage(const QString &message)
{
    if (message != _message) {
        _message = message;
        emit messageChanged();
    }
}

QString DialogObject::dateTime() const
{
    return _dateTime;
}

void DialogObject::setDateTime(const QString &dateTime)
{
    if (dateTime != _dateTime) {
        _dateTime = dateTime;
        emit dateTimeChanged();
    }
}
