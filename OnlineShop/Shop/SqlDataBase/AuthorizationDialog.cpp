#include "AuthorizationDialog.hpp"
#include "ui_AuthorizationDialog.h"

AuthorizationDialog::AuthorizationDialog(SqlDatabaseHandler *dataBase, QWidget *parent) :
    QDialog(parent),
    m_sqlDataBaseHandler(dataBase),
    ui(new Ui::AuthorizationDialog)
{
    ui->setupUi(this);

    QVariantMap sqlSettings = m_sqlDataBaseHandler->GetDataClassEntity()->GetSqlConnectionSettings();


    QString serverAdres ="DESKTOP-FLRPPRB\\SQLEXPRESS19" ;
    QString dataBaseName = "unicomps";
    QString userName = "sa";
    QString password = "1234";


    if(!sqlSettings.isEmpty())
    {
        serverAdres = sqlSettings.value("serverAdres").toString();
        dataBaseName = sqlSettings.value("dataBaseName").toString();
        userName = sqlSettings.value("userName").toString();
        password = sqlSettings.value("password").toString();
    }

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
        QVariantMap settingMap;
        settingMap.insert("serverAdres", ui->serverAddressLineEdit->text());
        settingMap.insert("dataBaseName", ui->dataBaseLineEdit->text());
        settingMap.insert("userName", ui->loginLineEdit->text());
        settingMap.insert("password", ui->passwordLineEdit->text());
        m_sqlDataBaseHandler->GetDataClassEntity()->SetSqlConnectionSettings(settingMap);

        QMessageBox::information(this, tr("Sql connection to server"),
                                         tr("Succes connection"));
        this->hide();
    }
    else
    {
        ui->connectPushButton->setText("Connect to server");
        QMessageBox::warning(this, tr("Sql connection to server"),
                                         tr("Error connection"));
    }
}
