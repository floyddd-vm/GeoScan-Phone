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
    int i = 0; int j;
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
                 j = 0; fields = "";
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
    if (!sdb.open()) {
        qDebug() << sdb.lastError().text();
    }
    else{
        qDebug() << "Соединение установлено";
    }
}

//Метод поиска контакта по номеру, возвращает id
int DataBase::getIdContact(QString number)
{


}



/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{

    this->sdb.close();
    this->sdb.removeDatabase("QSQLITE");
    qDebug() << "DB is closed";
}

/*Чтение данных T_Fields из таблицы T_Name*/
QSqlQuery DataBase::readTable(QString T_Name, QString T_Fields){

    QSqlQuery query;

    QString i = "1";

    query.prepare(
        QString("SELECT %"+i+" FROM %2;").arg(T_Fields).arg(T_Name)
    );

    if (!query.exec()) {
            qDebug() << query.lastError().text();
        }

    return query;
}

bool DataBase::insertIntoTable(QString T_Name, QVariantList &data){

        /* Запрос SQL формируется из QVariantList,
         * в который передаются данные для вставки в таблицу.
         * */
        sdb.transaction();
        QSqlQuery query;
        int table_num = tNames.indexOf(T_Name);
        QString fields = tFieldNames.at(table_num);

        qDebug() << data.count();

        if( data.count() != fields.count(",")+1 ){
            qDebug() << "Количество полученных аргументов не совпадает с числом полей таблицы!";
            return -1;
        }

        QString prep;
        /* В начале SQL запрос формируется с ключами,
         * которые потом связываются методом bindValue
         * для подстановки данных из QVariantList
         * */
        qDebug() << QString( "INSERT INTO "+T_Name+" ("+fields+") VALUES (" + data.at(0).toString() +","+  data.at(1).toString()+ "," + data.at(2).toString() + "," + data.at(3).toString()+ "," + data.at(4).toString() +")");

        bool b = query.exec(
            "INSERT INTO "+T_Name+" ("+fields+") VALUES (" + data.at(0).toString() +","+  data.at(1).toString()+ ", '" + data.at(2).toString() + "', '" + data.at(3).toString() + "', '" + data.at(4).toString() + "')"
        );

        if (!b) {
            qDebug() << "1  Кажется данные не вставляются, проверьте дверь, может она закрыта?";
        }
/*
        QString str_insert = "INSERT INTO "+T_Name+" ("+fields+") "
                    "VALUES (%1, %2, '%3', '%4', '%5');";
        QString str = str_insert.arg( data.at(0).toString() )
                                .arg( data.at(1).toString() )
                                .arg( data.at(2).toString() )
                                .arg( data.at(3).toString() )
                                .arg( data.at(4).toString() );
        b = query.exec(str);
        qDebug() << str;
        if (!b) {
                qDebug() << "2  Кажется данные не вставляются, проверьте дверь, может она закрыта?";
        }
*/

        sdb.commit();
/*

        prep = "INSERT INTO "+T_Name+" ("+fields+")";
        switch (data.count()) {
        case 1:
            prep += " VALUES (%1);";
            query.prepare(
                        prep.arg(data.at(0));
            );

            break;
        case 2:
            prep += " VALUES (%1, %2);";
            query.prepare(
                        prep.arg(data.at(0)).arg(data.at(1));
            );

            break;
        case 3:
            prep += " VALUES (%1, %2, %3);";
            query.prepare(
                        prep.arg(data.at(0)).arg(data.at(1)).arg(data.at(2));
            );

            break;
        case 4:
            prep += " VALUES (%1, %2, %3, %4);";
            query.prepare(
                        prep.arg(data.at(0)).arg(data.at(1)).arg(data.at(2)).arg(data.at(3));
            );

            break;
        default:
            break;
        }

*/
//        query.prepare(
//            QString("SELECT %"+i+" FROM %2;").arg(T_Fields).arg(T_Name)
//        );
//        query.prepare("INSERT INTO " T_Name " ( " + fields + "
//                      "VALUES (:FName, :SName, :Nik)");
//        query.bindValue(":FName",       data[0].toString());
//        query.bindValue(":SName",       data[1].toString());
//        query.bindValue(":Nik",         data[2].toString());

}
