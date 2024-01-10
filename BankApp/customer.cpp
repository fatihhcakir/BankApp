#include "customer.h"


// Constructor
Customer::Customer(QString id) {

    if(!connOpen()){
        qDebug() << "Failed to customer database";
        return;
    }

    QSqlQuery qry;
    qry.prepare("Select * from Customer where ID = '"+id+ "'");

    if(qry.exec()){
        connClose();
        if(!qry.next()){return;}

        this->id = qry.value(0).toInt();
        this->name=qry.value(1).toString();
        this->surname= qry.value(2).toString();
        this->phoneNumber = qry.value(4).toString();

        vector<QString> accountsIDlist(0);
        QString accounts_str = qry.value(6).toString();

        QString accountID;

        int i = 0;
        int accountCounter=0;
        while(accounts_str.at(i).isDigit()){
            accountID.append(accounts_str.at(i));
            if(accounts_str.at(i+1)== ','){
                accountCounter++;
                accountsIDlist.push_back(accountID);
                accountID.clear();
                accountID = "";
                i+=2;
                continue;
            }
            if(accounts_str.at(i+1)==';'){
                accountCounter++;
                accountsIDlist.push_back(accountID);
                accountID.clear();
                accountID = "";
                break;
            }
            i++;
        }
        vector<Account> accounts(0);
        for(int i = 0;i < accountCounter;i++){
            switch(i){
            case 0:
                accounts.push_back(TLAccount(accountsIDlist.at(i)));
                break;
            case 1:
                accounts.push_back(USDAccount(accountsIDlist.at(i)));
                break;
            case 2:
                accounts.push_back(EURAccount(accountsIDlist.at(i)));
                break;
            }
        }

        this->accounts = accounts;
        setOperations();


        showAccountInfo();
    }
}

void Customer::showAccountInfo(){
    qDebug()<< accounts.size();

    for(int i = 0; i < (int)accounts.size();i++){
        QString temp ;
        temp.setNum(accounts.at(i).getBalance());
        qDebug() << accounts.at(i).getAccountID() + "--" + temp + "--"+ accounts.at(i).getType();

    }
}

float Customer::exchangeMoney(int from,int to,float value){
    float ratio = 1;
    if(from == 0 && to == 0)ratio = 1;
    if(from == 1 && to == 1)ratio = 1;
    if(from == 2 && to == 2)ratio = 1;
    if(from == 0 && to == 1)ratio = 1.0/30.0;
    if(from == 0 && to == 2)ratio = 1.0/40.0;
    if(from == 1 && to == 0)ratio = 30;
    if(from == 1 && to == 2)ratio = 0.75;
    if(from == 2 && to == 1)ratio = 4.0/3.0;
    if(from == 2 && to == 0)ratio = 40;

    if(!connOpen()){
        qDebug()<<"could not connect to the database";
    }
    QString balanceNew;
    balanceNew.setNum(this->getAccounts().at(from).getBalance()-value);
    QSqlQuery qry ;

    qry.prepare("update Account set Balance = '"+balanceNew+"' where accountID = '"+this->getAccounts().at(from).getAccountID()+"'");
    qry.exec();
    QString toBalanceNew;
    toBalanceNew.setNum(this->getAccounts().at(to).getBalance()+ value*ratio);
    qry.prepare("update Account set Balance = '"+toBalanceNew+"' where accountID = '"+this->getAccounts().at(to).getAccountID()+"'");
    qry.exec();
    Operation ("exchanged money",this->getAccounts().at(from).getAccountID(),this->getAccounts().at(to).getAccountID(),value*ratio);;

    return value*ratio;
}

vector<QString>Customer::setOperations(){
    vector<QString>operations;
    if(!connOpen()){qDebug()<<"could not connect to database!";}

    QSqlQuery qry;
    for(int i = 0;i < (int)this->getAccounts().size();i++){
        qry.prepare("select * from Operation where fromAccount= '"+this->getAccounts().at(i).getAccountID()+"'");
        qry.exec();
        QString operation= "";
        while(qry.next()){
            operation.append(qry.value(0).toString())
                .append(" from ")
                .append(qry.value(1).toString())
                .append(" to ")
                .append(qry.value(2).toString())
                .append(" amount of ")
                .append(qry.value(3).toString());
            operations.push_back(operation);

            operation = "";
        }
    }
    connClose();
    return operations;

}


/*
float Customer::makePayment(){}
float Customer::withdrawLoan(){}
*/
