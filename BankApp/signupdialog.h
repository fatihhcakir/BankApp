#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include "QtSql"
#include "QtDebug"
#include "QFileInfo"
#include "invaccount.h"

namespace Ui {
class SignupDialog;
}

class SignupDialog : public QDialog
{
    Q_OBJECT

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

public:
    explicit SignupDialog(QWidget *parent = nullptr);
    ~SignupDialog();

private slots:
    void on_signupButton_clicked();

    void on_loginButton_clicked();

    QString createRecovery();

private:
    Ui::SignupDialog *ui;

};

#endif // SIGNUPDIALOG_H
