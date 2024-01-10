#include "account.h"


Account::Account(){}

Account::Account(QString accountID) {

    if(!connOpen()){
        qDebug() << "Could not connect to database!";
    }

    QSqlQuery qry;
    qry.prepare("select * from Account where accountID ='"+accountID+"'");
    qDebug()<< "select * from Account where accountID ='"+accountID+"'";

    if(qry.exec()){
        if(! qry.next()){return;}
        this->accountID = qry.value(0).toString();
        this->ownerID = qry.value(1).toString();
        this->balance = qry.value(2).toFloat();
        this->type = qry.value(3).toString();


    }
}

float Account::getBalance(){return balance;}
QString Account::getAccountID(){return this->accountID;}
QString Account::getOwnerID(){return ownerID;}


// DENEME BAŞLANGIÇ

int Account::getCounterID(){
    QSqlQuery qry;

    qry.prepare("select accountID from Account where ownerID = '0'");
    if(qry.exec()){
        if(qry.next()){
            setCounterID(qry.value(0).toInt());
            return qry.value(0).toInt();
        }
    }
    return 0;

}


void Account::setCounterID(int currID){

    QSqlQuery qry;


    if(qry.exec()){
        if(qry.next()){
            currID = qry.value(0).toInt();
        }
    }
    currID += 4;
    QString temp = "";
    temp.setNum(currID);
    qry.prepare("update Account set accountID = " +temp+ " where ownerID = '0'" );
    if(qry.exec()){
        qDebug()<< "Current ID counter is "+temp;
    }

    return;
}
// DENEME SON

float Account::changeBalance(float changeAmount,QString targetAccountID){
    qDebug()<< "CHANGE BALANCE START ";


    if(!connOpen()){
        qDebug()<< "Failed to connect to Account database";
        return 0.0;
    }

    QString balanceNew;
    QString targetBalance;
    this->getAccountID();

    QSqlQuery qry;
    qry.prepare("select Balance from Account where accountID= '"+this->getAccountID()+"'");

    if(qry.exec()){
        if(qry.next()){
            balanceNew.setNum( qry.value(0).toFloat()-changeAmount);
        }
    }
    if(balanceNew.toFloat() < 0){return 0.0;}

    qry.prepare("select Balance from Account where accountID='"+targetAccountID+"'");
    if(qry.exec()){
        if(!qry.next()){
            qDebug()<<"There is no target account with this ID";
            return 0.0;
        }
        targetBalance.setNum( qry.value(0).toFloat()+changeAmount);
    }

    qry.prepare("UPDATE Account SET Balance = '"+balanceNew+"' where accountID= '"+this->getAccountID()+"'");
    qry.exec();
    qry.prepare("UPDATE Account SET Balance = '"+targetBalance+"' where accountID= '"+targetAccountID+"'");
    qry.exec();
    Operation("Send money",this->getAccountID(),targetAccountID,changeAmount);
    Operation("Received money",targetAccountID,this->getAccountID(),changeAmount);
    return changeAmount;
}

void Account::createAccount(QString accountID,QString ownerID,QString type){

    QSqlQuery qry;
    qry.prepare("insert into Account (accountID,ownerID,Balance,type) values ('"+accountID+"','"+ownerID+"',0,'"+type+"')");
    qry.exec();

}

