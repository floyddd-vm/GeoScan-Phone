#ifndef DATAOBJECT_H
#define DATAOBJECT_H
#include <QObject>

class DialogObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qlonglong id READ id WRITE setId NOTIFY idChanged)    
    Q_PROPERTY(QString contact READ contact WRITE setContact NOTIFY contactChanged)
    Q_PROPERTY(qlonglong status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(QString dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged)

public:

    DialogObject(QObject *parent=0);
    DialogObject(const qlonglong &id, const QString &contact, const qlonglong &status ,const QString &dateTime,  const QString &message, QObject *parent=0);

    qlonglong id() const;
    void setId(qlonglong &id);

    QString contact() const;
    void setContact(const QString &contact);

    qlonglong status() const;
    void setStatus(const qlonglong &status);

    QString message() const;
    void setMessage(const QString &message);

    QString dateTime() const;
    void setDateTime(const QString &dateTime);

signals:
    void contactChanged();
    void messageChanged();
    void dateTimeChanged();
    void idChanged();
    void statusChanged();

private:
    qlonglong _id;
    qlonglong _status;
    QString _contact;
    QString _message;
    QString _dateTime;

};

#endif // DATAOBJECT_H
