#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_NAME       "C:\\Users\\floyd\\Documents\\qt\\phone\\ANTON\\serviceApp\\DB\\Contacts.sqlite"
#define T_CONTACTS          "contacts"
#define T_LOGS              "logs"
#define T_MESSAGES          "messages"
#define T_STATUS            "status"



class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     *
     * */
    QSqlQuery readTable(QString T_Name, QString T_Fields);
    bool insertIntoTable(QString T_Name, QVariantList &data);

//    bool inserIntoTable(const QVariantList &data);
public:
    QSqlQuery query;    

    int getIdContact(QString number);

    //Инициализировать служебные массивы данных с именами таблиц и именами полей каждой таблицы:
    void getTInfo();
private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase sdb;
    QStringList tNames;
    QStringList tFieldNames;

private:
    /* Внутренние методы для работы с базой данных
     * */
    //Подключиться к БД:
    void connectToDataBase();
//    bool openDataBase();
//    bool restoreDataBase();

    //Разорвать соединение с БД:
    void closeDataBase();
//    bool createTable();
};




#endif // DATABASE_H

