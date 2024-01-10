#include "invaccount.h"


InvAccount::InvAccount(QString accountID):Account(accountID){
}
InvAccount::InvAccount(){}

vector<float> InvAccount::getInvestments (){
    return invests;

}
bool  InvAccount::setInvestments(QString accountID){

    if(!connOpen()){
        qDebug()<< "Failed to connect to database";
        return false;
    }

    QSqlQuery qry;

    qry.prepare("select Balance from Investment where accountID = '"+accountID+"'");
    vector <float> investments;

    if(qry.exec()){
        int counter= 0;
        while(qry.next()){
            investments.push_back(qry.value(counter++).toFloat());
        }

    }
    if(investments.empty())return false;
    this->invests = investments;
    return true;
}


void InvAccount::createAccount(QString accountID){

    QSqlQuery qry;
    QString temp;
    temp.setNum(0.0);
    qry.prepare("insert into Investment(accountID,Balance,type) values ('"+accountID+"','"+temp+"','GOLD')");

    if(qry.exec()){
        qDebug()<<"gold account created successfully";
    }

    qry.prepare("insert into Investment(accountID,Balance,type) values ('"+accountID+"','"+temp+"','SILVER')");
    if(qry.exec()){
        qDebug()<<"silver account created successfully";
    }

}


float InvAccount::changeInvests(QString toType,float amount){
    QString balanceNew;
    QString targetBalance;


    QSqlQuery qry;
    qry.prepare("select Balance from Account where accountID= '"+this->getAccountID()+"'");

    if(qry.exec()){
        if(qry.next()){
            balanceNew.setNum( qry.value(0).toFloat()-amount);
        }
    }
    if(balanceNew.toFloat() < 0){return 0.0;}

    qry.prepare("select Balance from Investment where accountID='"+this->getAccountID()+"' and type= '"+toType+"'");
    if(qry.exec()){
        if(!qry.next()){
            qDebug()<<"There is no target account with this ID";
            return 0.0;
        }
        targetBalance.setNum( qry.value(0).toFloat()+(amount/2000.0));
    }

    qry.prepare("UPDATE Account SET Balance = '"+balanceNew+"' where accountID= '"+this->getAccountID()+"'");
    qry.exec();
    qry.prepare("UPDATE Investment SET Balance = '"+targetBalance+"' where accountID= '"+this->getAccountID()+"' and type= '" +toType+ "'");
    qry.exec();
    Operation((amount>0?"Bought ":"Sold " )+toType ,this->getAccountID(),this->getAccountID(),amount);

    return amount;
}


