#ifndef OPERATION_H
#define OPERATION_H
#include "QtDebug"
#include "QFileInfo"
#include "qsqldatabase.h"
#include "QtSql"


class Operation
{
public:
    Operation();
    Operation(QString operationName, QString accountID, QString targetAccountID, float amount);

    QString getOperationName(){return operationName;}
    QString getID(){return accountID;}
    QString getTargetID(){return targetAccountID;}
    float getAmount(){return amount;}


private:
    QString operationName;
    QString accountID;
    QString targetAccountID;
    float amount;

public :
    QSqlDatabase mydb;

    void connClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen(){
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        QFileInfo appPath(QCoreApplication::applicationDirPath());

        qDebug() << appPath.absoluteFilePath()+"/../BankApp/Bank.db";
        mydb.setDatabaseName(appPath.absoluteFilePath()+"/../../BankApp/Bank.db");
        if(!mydb.open()){
            qDebug() << "Failed to open the database";
            return false;
        }
        return true;
    }


};

#endif // OPERATION_H
