#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "signupdialog.h"
#include <QMainWindow>
#include "forgotdialog.h"
#include "QtSql"
#include "QtDebug"
#include "QFileInfo"
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
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
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();

    void on_signupButton_clicked();

    void on_forgotButton_clicked();

private:
    Ui::LoginWindow *ui;

    SignupDialog *singupDialog;
    ForgotDialog *forgotDialog;
    MainWindow *mainWindow;
};
#endif // LOGINWINDOW_H
