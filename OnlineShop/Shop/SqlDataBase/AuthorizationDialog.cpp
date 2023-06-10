#include "AuthorizationDialog.hpp"
#include "ui_AuthorizationDialog.h"

AuthorizationDialog::AuthorizationDialog(SqlDatabaseHandler *dataBase, QWidget *parent) :
    QDialog(parent),
    m_sqlDataBaseHandler(dataBase),
    ui(new Ui::AuthorizationDialog)
{
    ui->setupUi(this);

    QString serverAdres ="DESKTOP-FLRPPRB\\SQLEXPRESS19" ;
    QString dataBaseName = "unicomps";
    QString userName = "sa";
    QString password = "1234";

    ui->serverAddressLineEdit->setText(serverAdres);
    ui->dataBaseLineEdit->setText(dataBaseName);
    ui->loginLineEdit->setText(userName);
    ui->passwordLineEdit->setText(password);

    if(dataBase->isConnected())
    {
        ui->connectPushButton->setText("Connected to server");
    }
    else
    {
        ui->connectPushButton->setText("Connect to server");
    }
}



AuthorizationDialog::~AuthorizationDialog()
{
    delete ui;
}



bool AuthorizationDialog::isConnected()
{
    return m_isConnected;
}



void AuthorizationDialog::on_connectPushButton_clicked()
{
    if(m_sqlDataBaseHandler->MakeConection(ui->serverAddressLineEdit->text(), ui->dataBaseLineEdit->text(),
                                           ui->loginLineEdit->text(), ui->passwordLineEdit->text()))
    {
        ui->connectPushButton->setText("Connected to server");
    }
    else
    {
        ui->connectPushButton->setText("Connect to server");
    }
}
