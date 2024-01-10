#include "forgotdialog.h"
#include "ui_forgotdialog.h"
#include <QMessageBox>

ForgotDialog::ForgotDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ForgotDialog)
{

    ui->setupUi(this);
    ui->lineEdit_forgot_code->setPlaceholderText("Enter your forgot code");
    ui->lineEdit_forgot_id ->setPlaceholderText("Enter your ID");
    ui->lineEdit_forgot_password ->setPlaceholderText("Enter your new password");
    ui->lineEdit_confirm_password ->setPlaceholderText("Enter your new password again");

}

ForgotDialog::~ForgotDialog()
{
    delete ui;
}

void ForgotDialog::on_pushButton_login_clicked()
{
    this->close();

}


void ForgotDialog::on_pushButton_confirm_clicked()
{
    QString id= ui->lineEdit_forgot_id->text();
    QString recovery= ui->lineEdit_forgot_code->text();
    QString newPassword = ui->lineEdit_forgot_password->text();
    QString confirmPassword = ui->lineEdit_confirm_password->text();


    if(!connOpen()){
        QMessageBox::warning(this,"Login","Could not connect the database!");
        qDebug()<<"Failed to open the Database";
        return ;
    }

    QSqlQuery qry;
    qry.prepare("select * from Customer where ID ='"+id + "'and recovery = '"+recovery+"'");

    if(qry.exec()){

        int count = 0;
        while (qry.next()){count++;}

        if(count !=1 ){

            QMessageBox::warning(this,"Account Error", "Account not found!");
            return;
        }
        if(newPassword != confirmPassword){
            QMessageBox::warning(this,"Wrong Password", "Passwords dont match!!!");
            return;
        }
        qry.prepare("update Customer set password = '"+newPassword+"'where ID = '"+id+"'");

        if(qry.exec()){
            QMessageBox::information(this,"Successfull!", "Password set succesfully!");
            return;
        }

    }
}
