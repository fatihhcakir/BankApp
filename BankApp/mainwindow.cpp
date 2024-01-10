#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent,QString idNumber)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,idNumber(idNumber)
    ,customer(idNumber)
{
    ui->setupUi(this);
    float balance = customer.getAccounts().at(0).getBalance();
    QString text=QString::number(balance,'f',2);
    text.append(' ').append(customer.getAccounts().at(0).getType());


    ui->label_balance->setText(text);
    ui->label_id->setText(idNumber);
    ui->stackedWidget->setCurrentIndex(0);
    vector <QString> operations =customer.setOperations();

    for(int i    = 0; i < (int)operations.size();i++){
        ui->listWidgetActivities->addItem(operations.at(i));
    }





}

MainWindow::~MainWindow()
{
    delete ui;
}

//homepage
void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    float balance = customer.getAccounts().at(0).getBalance();
    QString text=QString::number(balance,'f',2).append(' ');
    text.append(customer.getAccounts().at(0).getType());
    ui->label_balance->setText(text);

    ui ->label_id->setText(idNumber);


    // use this balance and show it on user interface

}

//My accounts
void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    float balance = customer.getAccounts().at(0).getBalance();
    QString text=QString::number(balance,'f',2).append(' ');
    text.append(customer.getAccounts().at(0).getType());
    ui ->textBrowser ->setText(text);
    ui ->textBrowser_2 ->setText(text);
    ui ->textBrowser_balance ->setText(text);





}

//money transfer
void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    float balance = customer.getAccounts().at(0).getBalance();
    QString text=QString::number(balance,'f',2).append(' ');
    text.append(customer.getAccounts().at(0).getType());
    ui ->label_4->setText(text);

}

//exchange money
void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

}

//investments
void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

//loans
void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

}

//home page
void MainWindow::on_toolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

//my accounts
void MainWindow::on_tlButton_clicked()
{

    ui->accountsWidget->setCurrentIndex(0);
    float balance = customer.getAccounts().at(0).getBalance();
    QString text=QString::number(balance,'f',2).append(' ');
    text.append(customer.getAccounts().at(0).getType());
    ui ->textBrowser->setText(text);

}

//my accounts
void MainWindow::on_dolarButton_clicked()
{
    ui->accountsWidget->setCurrentIndex(1);
    float balance = customer.getAccounts().at(1).getBalance();
    QString text=QString::number(balance,'f',2).append(' ');
    text.append(customer.getAccounts().at(1).getType());

    ui ->textBrowser_2->setText(text);


}

//my accounts
void MainWindow::on_euroButton_clicked()
{
    ui->accountsWidget->setCurrentIndex(2);
    float balance = customer.getAccounts().at(2).getBalance();
    QString text=QString::number(balance,'f',2).append(' ');
    text.append(customer.getAccounts().at(2).getType());

    ui ->textBrowser_balance->setText(text);

}






void MainWindow::on_pushButton_sendMoney_clicked()
{
    QString  toAccountID = ui->lineEdit_id->text();
    float amount = ui->lineEdit_amount->text().toFloat();

    // TODO: CHECK THE EXISTANCE OF THE ACCOUNT


    if(amount <=0 || amount > customer.getAccounts().at(0).getBalance()){
        ui->label_33->setText("Could not send the money!");
        QMessageBox::warning(this,"SEND","Could not send the money!");
        return;
    }
    QString str;

    str.setNum(customer.getAccounts().at(0).changeBalance(amount,toAccountID));
    ui->label_33->setText("Successfully send money!");


}


void MainWindow::on_pushButton_convert_clicked()
{
    QString from = ui->comboBox_exchange_from->currentText();
    QString to = ui->comboBox_exchange_to->currentText();
    float value = ui->lineEdit_exchange_amount->text().toFloat();
    int fromint= 0,toint= 0;
    if(from == "USD"){fromint = 1;}
    if(from == "EUR"){fromint = 2;}
    if(to == "USD"){toint = 1;}
    if(to == "EUR"){toint = 2;}

    QString str1,str2;
    str1.setNum(customer.exchangeMoney(fromint,toint,value));
    str2.setNum(value);
    ui->label_40->setText("Successfully exchanged "+str2+""+from +" to "+str1+to );

}

