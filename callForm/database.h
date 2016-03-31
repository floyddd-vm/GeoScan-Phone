#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_NAME       "C:\\Users\\anton\\Desktop\\QMLForms\\Contacts.sqlite"
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
    //Получить данные из таблицы
    QSqlQuery readTable(QString T_Name, QString T_Fields);
    //Вставить данные в таблицу
    bool insertIntoTable(QString T_Name, QVariantList &data);
    //Получить данные по параметрам
    QSqlQuery findInfoByParams(QString T_Name, QString param, QVariant value);
    QSqlQuery sortFindInfoByParams(QString T_Name, QString param, QVariant value);
    //Изменение данных в таблице "Контакты"
    bool updateTContacts(QStringList setFields, QStringList values, int id);
    //Удаление данных
    bool deleteFromTable(QString T_Name, QString param, QVariant value);
    QSqlQuery getDialog();
//    bool inserIntoTable(const QVariantList &data);
public:
    QSqlQuery query;

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

    //Инициализировать служебные массивы данных с именами таблиц и именами полей каждой таблицы:
    void getTInfo();

    //Разорвать соединение с БД:
    void closeDataBase();

    //Попытаться выполнить запрос
//    void tryExec(QString methodName, QSqlQuery &query);
};




#endif // DATABASE_H

