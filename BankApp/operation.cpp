#include "operation.h"
#include <QMessageBox>


Operation::Operation(QString operationName, QString accountID, QString targetAccountID, float amount) {

    if(!connOpen()){
        qDebug()<<"Failed to open the Database";
        return ;
    }

    QSqlQuery qry;


    QString str;
    str.setNum(amount);
    qry.prepare("insert into Operation(operationName,fromAccount,toAccount,amount) values ('"+operationName+"','"+accountID+"','"+targetAccountID+"','"+str+"')");
    if (qry.exec()){
        qDebug()<<"Operation created succesfuly";
    }

}
