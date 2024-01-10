#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <account.h>
#include <tlaccount.h>
#include <euraccount.h>
#include <usdaccount.h>
#include <operation.h>
#include <vector>
#include "QtDebug"
#include "QFileInfo"

class Customer
{
public:
    Customer(QString id);

    void showAccountInfo();


    float makePayment();
    float exchangeMoney(int from,int to,float value);
    float withdrawLoan();

    //getters-setters
    int getID(){return id;}
    vector<Account> getAccounts(){return accounts;}
    vector<QString> getOperations(){return operations;}
    vector<QString> setOperations();
    QString getName(){return name;}
    QString getSurname(){return surname;}
    QString getPhoneNumber(){return phoneNumber;}

private:

    int id;
    vector<Account> accounts;
    vector<QString> operations;
    QString name;
    QString surname;
    QString phoneNumber;



public :
    QSqlDatabase mydb;

    void connClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen(){
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        QFileInfo appPath (QCoreApplication::applicationDirPath());

        qDebug() << appPath.absoluteFilePath()+"/../BankApp/Bank.db";
        mydb.setDatabaseName(appPath.absoluteFilePath()+"/../../BankApp/Bank.db");
        if(!mydb.open()){
            qDebug() << "Failed to open the database";
            return false;
        }
        return true;
    }




};






#endif // CUSTOMER_H
