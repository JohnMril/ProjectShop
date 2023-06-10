#ifndef AUTHORIZATIONDIALOG_HPP
#define AUTHORIZATIONDIALOG_HPP

#include <QDialog>
#include <QMessageBox>
#include "SqlDatabseHandler.hpp"


namespace Ui {
class AuthorizationDialog;
}

class AuthorizationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationDialog(SqlDatabaseHandler* dataBase, QWidget *parent = nullptr);
    ~AuthorizationDialog();

    bool isConnected();

private slots:
    void on_connectPushButton_clicked();

private:

    SqlDatabaseHandler* m_sqlDataBaseHandler;

    bool m_isConnected = false;

    Ui::AuthorizationDialog *ui;
};

#endif // AUTHORIZATIONDIALOG_HPP
