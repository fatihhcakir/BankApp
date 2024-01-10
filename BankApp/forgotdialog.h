#ifndef FORGOTDIALOG_H
#define FORGOTDIALOG_H

#include <QDialog>
#include "QtSql"
#include "QtDebug"
#include "QFileInfo"

namespace Ui {
class ForgotDialog;
}

class ForgotDialog : public QDialog
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
    explicit ForgotDialog(QWidget *parent = nullptr);
    ~ForgotDialog();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_confirm_clicked();

private:
    Ui::ForgotDialog *ui;
};

#endif // FORGOTDIALOG_H
