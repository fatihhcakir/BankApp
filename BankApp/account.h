#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <vector>
#include "QtSql"
#include "QtDebug"
#include "QFileInfo"
#include "operation.h"
using namespace std;


class Account
{
public:
    Account(QString accountID);
    Account();

    static void createAccount(QString accountID,QString ownerID,QString type);
    int getCounterID();
    void setCounterID(int currID);
    QString getOwnerID();
    QString getAccountID();
    float getBalance();
    float changeBalance(float changeAmount,QString targetAccountID);
    float sendMoney(float amount,QString targetAccountID);
    virtual QString getType()const{return type;}

private:
    QString accountID;
    QString ownerID;
    float balance;
    QString type;


public:
    QSqlDatabase mydb;

    void connClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen(){
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        QFileInfo dbPath (QCoreApplication::applicationDirPath());

        qDebug() << dbPath.absoluteFilePath()+"/../BankApp/Bank.db";
        mydb.setDatabaseName(dbPath.absoluteFilePath()+"/../../BankApp/Bank.db");
        if(!mydb.open()){
            qDebug() << "Failed to open the database";
            return false;
        }
        return true;
    }





};

#endif // ACCOUNT_H
