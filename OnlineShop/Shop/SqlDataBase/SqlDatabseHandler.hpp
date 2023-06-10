#ifndef SQLDATABSEHANDLER_HPP
#define SQLDATABSEHANDLER_HPP

#include <QObject>
#include <QWidget>
#include <QtSql>
#include <QDebug>
#include <QSqlTableModel>

#include "DataClass/DataClass.hpp"
#include "SenderDataDialog.hpp"
#include "AskToUseSettingsDialog.hpp"

class SqlDatabaseHandler : public QWidget
{
    Q_OBJECT
public:
    explicit SqlDatabaseHandler(DataClass* dataClass, QWidget *parent = nullptr);

    bool isConnected() const;
    bool MakeConection(QString serverAdres, QString dataBaseName, QString userName, QString password);

    void PrepareToSend(QString shopName);

signals:
    void NeedToConnect();
    void SendData(QString);

private slots:
    void SendDataToSqlServer(const QString& shopName);

    void EmitSenderDialog(const QString&  shop);

    int CheckSqlTableRows();
    bool EmitSqlScript();

    bool ClearSqlTable();

private:


    bool m_isConnected = false;

    SenderDataDialog* m_senderDataDialog;

    DataClass* m_dataClass;

    AskToUseSettingsDialog* m_askDialog = nullptr;

    QSqlDatabase m_dataBase;

};

#endif // SQLDATABSEHANDLER_HPP
