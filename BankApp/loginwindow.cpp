#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <customer.h>
LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->lineEdit_ID->setPlaceholderText("Enter your ID");
    ui->lineEdit_password->setPlaceholderText("Enter your password");
    ui->loginButton->setShortcut(QKeySequence(Qt::Key_Enter));

}

LoginWindow::~LoginWindow()
{
    connClose();
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString IdNumber = ui->lineEdit_ID->text();
    QString password = ui->lineEdit_password->text();


    //Connect the database

    if(!connOpen()){
        QMessageBox::warning(this,"Login","Could not connect the database!");
        qDebug()<<"Failed to open the Database";
        return ;
    }



    if(IdNumber.length() == 0 || password.length() == 0){
        QMessageBox::warning(this,"Login","ID number or Password cannot be blank!!!");
        connClose();
        return;
    }
    QSqlQuery qry;

    qry.prepare("select * from Customer where ID ='"+IdNumber + "'and password='"+password+"'");

    if(qry.exec()){

        int count = 0;
        while (qry.next()){count++;}

        if(count ==1 ){

            mainWindow = new MainWindow(this,IdNumber);
            mainWindow->show();

        }
        else{
            QMessageBox::warning(this,"Login", "Id Number and password is not correct");
        }
    }

    connClose();


}


void LoginWindow::on_signupButton_clicked()
{
    singupDialog = new SignupDialog(this);
    singupDialog->show();

}


void LoginWindow::on_forgotButton_clicked()
{
    forgotDialog = new ForgotDialog(this);
    forgotDialog->show();
}

