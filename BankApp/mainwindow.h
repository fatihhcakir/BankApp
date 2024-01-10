#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <customer.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr,QString idNumber = "0");
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_toolButton_clicked();

    void on_tlButton_clicked();

    void on_dolarButton_clicked();

    void on_euroButton_clicked();

    void on_pushButton_sendMoney_clicked();

    void on_pushButton_convert_clicked();

private:
    Ui::MainWindow *ui;
    QString idNumber;
    Customer customer;
};

#endif // MAINWINDOW_H
