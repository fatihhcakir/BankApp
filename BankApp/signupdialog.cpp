#include "signupdialog.h"
#include "ui_signupdialog.h"
#include <QMessageBox>
#include <string>


SignupDialog::SignupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignupDialog)
{
    ui->setupUi(this);
    ui->lineEdit_id->setPlaceholderText("Enter your ID");
    ui->lineEdit_name->setPlaceholderText("Enter your name");
    ui->lineEdit_surname->setPlaceholderText("Enter your surname");
    ui->lineEdit_phone->setPlaceholderText("Enter your number");
    ui->lineEdit_password_sign->setPlaceholderText("Enter your password ");
    ui->lineEdit_id_confirm_sign->setPlaceholderText("Enter your password again");


}

SignupDialog::~SignupDialog()
{
    delete ui;
}

static std::string keys ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
static int RecoveryCodeLength = 6;
QString SignupDialog::createRecovery(){
    QString code = "";
    int random ;
    for (int i = 0; i < RecoveryCodeLength; ++i) {
        random = rand() % 60;
        code.append(keys.at(random));
    }

    return code;
}

void SignupDialog::on_signupButton_clicked()
{



    QString name = ui->lineEdit_name->text();
    QString surname = ui->lineEdit_surname->text();
    QString id = ui->lineEdit_id->text();
    QString phone = ui->lineEdit_phone->text();
    QString password = ui->lineEdit_password_sign->text();
    QString confirm_password = ui->lineEdit_id_confirm_sign->text();
    QDate birthDate = ui->dateEdit->date();
    auto today = QDate::currentDate();
    auto age = today.year() - birthDate.year();




    if(name.isEmpty() || surname.isEmpty() || phone.isEmpty() || id.isEmpty() ||password.isEmpty() || confirm_password.isEmpty()){
        QMessageBox::warning(this,"Error", "Please, fill in the all blanks.");
        return;
    }
    if(password!=confirm_password){
        QMessageBox::warning(this,"Wrong Password", "Passwords dont match!!!");
        return;
    }
    if(age<18){
        QMessageBox::warning(this,"Age Error", "You cannot sign up.");
        return;
    }

    //creates the connection to database

    if(!connOpen()){
        QMessageBox::warning(this,"Login","Could not connect the database!");
        qDebug()<<"Failed to open the Database";
        return ;
    }



    QSqlQuery qry;
    qry.prepare("select * from Customer where ID ='"+id+"'");
    if(qry.exec()){

        int count = 0;
        while (qry.next()){count++;}

        if(count ==1 ){
            QMessageBox::warning(this,"Have Account Error", "You already have an account!");

            return;
        }

        QString recovery = createRecovery();

        QString str,temp;


        qDebug()<<"PROBLEM ABOUT STRING OR ANYTHING";
        int counterID = Account().getCounterID();
        str.setNum(counterID);
        Account().createAccount(QString::number(counterID),id,"TL");
        str.append(',');
        str.append(QString::number(counterID+1));

        Account().createAccount(QString::number(counterID+1),id,"USD");
        str.append(',');

        str.append(QString::number(counterID+2));
        qDebug()<<str;

        Account().createAccount(QString::number(counterID+2),id,"EUR");
        str.append(',');

        str.append(QString::number(counterID+3));
        qDebug()<<str;
        Account().createAccount(QString::number(counterID+3),id,"INV");
        InvAccount().createAccount(QString::number(counterID+3));
        str.append(';');




        QSqlQuery qry2;

        qry2.prepare("insert into Customer(ID,name,surname,password,phoneNumber,accounts,recovery) values ('"+id+"','"+name+"','"+surname+"','"+password+"','"+phone+"','"+str+"','"+recovery+"')");
        qDebug()<<qry2.lastQuery();




        if(qry2.exec()){
            QMessageBox::information(this,"Signed up", "Succesfully, signed up.\n  Account recovery code : "+recovery);

            return;
        }


        QMessageBox::warning(this,"Error", "Could not create the account!");

    }


}


void SignupDialog::on_loginButton_clicked()
{
    this->close();
}

