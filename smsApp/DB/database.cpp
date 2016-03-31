#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    // Подключение к базе данных
    connectToDataBase();
    //Получение списка таблиц и имён полей для каждой таблицы
    getTInfo();
}

DataBase::~DataBase()
{
    closeDataBase();
}

//Получение списка таблиц и имён полей для каждой таблицы
void DataBase::getTInfo(){
    int i = 0;
    QSqlQuery query_tn, query_tf;
    QString fields = "", fname = "";
    //Получение имён неслужебных таблиц БД
    if(!query_tn.exec("SELECT name FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite%';")){
        qDebug() << "Ошибка при выполнении запроса на выборку имён таблиц базы данных";
    }
    else{
        while (query_tn.next()) {
                tNames << query_tn.record().value(0).toString();
//                qDebug() << tNames.at(i);
                fields = "";
                if(!query_tf.exec("PRAGMA table_info("+tNames.at(i)+");")){
                    qDebug() << "Ошибка при выполнении запроса на выборку имён полей таблицы"+tNames.at(i);
                }
                else{
                    while (query_tf.next()) {
//                            qDebug() << query_tf.record().value(5);
                            if( query_tf.record().value(5).toString() != "1")
                            fields += " "+ query_tf.record().value(1).toString() + ",";
                //            contacts << data.record().value(0).toString() + " " + data.record().value(1).toString();
                //            qDebug() << contacts.at(i);
                //            i++;
                        }
                    fields.chop(1);//удаление ненужной запятой в конце
                    tFieldNames << fields+" ";
//                    qDebug() << tFieldNames.at(i);
                }
                i++;
            }
    }

//    qDebug() << tFieldNames.at(tNames.indexOf(T_LOGS));

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */

    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(DATABASE_NAME);
    //Проблема: sdb.open срабатывает всегда, даже когда настоящего подключения к базе не произошло.
    //Решить проблему с заданием относительного пути к базе.
    if (!sdb.open()) {
        qDebug() << sdb.lastError().text();
    }
    else{
        qDebug() << "Соединение установлено";
    }
}


/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{

    this->sdb.close();
    this->sdb.removeDatabase("QSQLITE");
    qDebug() << "DB is closed";
}

//bool DataBase::tryExec(QString methodName, QSqlQuery &query){
//    if (!query.exec()) {
//        qDebug() << "Method "+methodName+" error: "+query.lastError().text();
//        return false;
//    }
//    return true;
//}

/*Чтение данных T_Fields из таблицы T_Name*/
QSqlQuery DataBase::readTable(QString T_Name, QString T_Fields){

    QSqlQuery query;

    query.prepare(
        QString("SELECT %1 FROM %2;").arg(T_Fields).arg(T_Name)
    );

    if (!query.exec()) {
        qDebug() << "Method readTable error: "+query.lastError().text();
    }

    return query;
}

//Параметрический запрос на выборку данных из БД
QSqlQuery DataBase::findInfoByParams(QString T_Name, QString param, QVariant value){
    QSqlQuery query;

    query.prepare(
        QString("SELECT * FROM %1 WHERE %2 = %3;").arg(T_Name).arg(param).arg(value.toString())
    );

    if (!query.exec()) {
        qDebug() << "Method findInfoByParams error: "+query.lastError().text();
    }
    return query;
}

//Сортированный по дате поиск в сообщениях по параметру
/**
 * @brief DataBase::sortFindInfoByParams
 * @param T_Name
 * @param param
 * @param value
 * @return
 */

QSqlQuery DataBase::sortFindInfoByParams(QString T_Name, QString param, QVariant value){
    QSqlQuery query;

    query.prepare(
        QString("SELECT *,max(DateTime) FROM %1 WHERE %2 = %3 GROUP BY MsgID ORDER BY DateTime asc").arg(T_Name).arg(param).arg(value.toString())
    );

    if (!query.exec()) {
        qDebug() << "Method findInfoByParams error: "+query.lastError().text();
    }
    return query;
}

//
bool DataBase::insertIntoTable(QString T_Name, QVariantList &data){

    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    int table_num = tNames.indexOf(T_Name);
    QString fields = tFieldNames.at(table_num);
    int i;

    if( data.count() != fields.count(",")+1 ){
        qDebug() << "Количество полученных аргументов не совпадает с числом полей таблицы!";
        return -1;
    }

    QString prep;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    prep = "INSERT INTO "+T_Name+" ("+fields+") VALUES(";

    for(i = 1; i <= data.count(); i++){
        prep += "?";
        if(i < data.count()){
            prep += ", ";
        }
    }

    prep += ");";

    query.prepare(prep);

    for(i = 0; i < data.count(); i++){
        query.addBindValue(data.at(i));
    }

    if (!query.exec()) {
        qDebug() << "Method insertIntoTable error: "+query.lastError().text();
        return false;
    }

    return true;
}

//Метод для обновления таблицы контактов
//setFields - обновляемые поля,
//values - новые значения полей,
//id - идентификатор обновляемой записи таблицы.
bool DataBase::updateTContacts(QStringList setFields, QStringList values, int id){

    QSqlQuery query;

    if(setFields.count() == 0 || values.count() == 0){
        qDebug() << "Method updateTableByParams error: Недостаточное число аргументов для выполнения запроса!";
        return -1;
    }

    QString prep = "UPDATE " T_CONTACTS " SET ";

    for(int i = 0; i < setFields.count(); i++){
       prep += setFields.at(i) + " = ? ";
       if(i < setFields.count()-1){
           prep += ", ";
       }
    }
    prep += "WHERE ID = ?";

    query.prepare(prep);

    for(int i = 0; i < values.count(); i++){
        query.addBindValue(values.at(i));
    }
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Method updateTableByParams error: "+query.lastError().text();
        return false;
    }

    return true;
}

bool DataBase::deleteFromTable(QString T_Name, QString param, QVariant value){

    QSqlQuery query;

    query.prepare(
        QString("DELETE FROM %1 WHERE %2 = %3;").arg(T_Name).arg(param).arg(value.toString())
    );

    if (!query.exec()) {
        qDebug() << "Method findInfoByParams error: "+query.lastError().text();
    }

    return true;
}

QSqlQuery DataBase::getDialog()
{
     QSqlQuery query;
        query.prepare("SELECT * ,max(DateTime)FROM messages GROUP BY ContactID order by DateTime desc");
        if (!query.exec()) {
            qDebug() << "Method insertIntoTable error: "+query.lastError().text();
        }
        return query;
}
