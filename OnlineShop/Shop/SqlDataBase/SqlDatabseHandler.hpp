#ifndef SQLDATABSEHANDLER_HPP
#define SQLDATABSEHANDLER_HPP

#include <QObject>
#include <QWidget>
#include <QtSql>
#include <QDebug>
#include <QSqlTableModel>
#include <QMessageBox>

#include "DataClass/DataClass.hpp"
#include "SenderDataDialog.hpp"
#include "AskToUseSettingsDialog.hpp"
#include "SqlDataClassThread.hpp"

class SqlDatabaseHandler : public QWidget
{
    Q_OBJECT
public:
    explicit SqlDatabaseHandler(DataClass* dataClass, QWidget *parent = nullptr);

    bool isConnected() const;
    bool MakeConection(QString serverAdres, QString dataBaseName, QString userName, QString password);
    void MakeConnection();

    void PrepareToSend(QString shopName);

    DataClass* GetDataClassEntity();



signals:
    void NeedToConnect();
    void SendData(QString);
    void ShowMainWindow();
    void Started(QString processName);
    void Finished(QString processName);


public slots:
    void SendDataToSqlServer(const QString& shopName);

    void EmitSenderDialog(const QString&  shop);

    void SendAllDataToSqlServer();

//    int CheckSqlTableRows();
    bool EmitSqlScript(QString shopName = "", bool switchKey = true);
    bool EmitSqlRecount();

    bool ClearSqlTable();

    void MessageBoxFromThread(bool state);
    void ConnectionCreated(bool state);

private:

    QVector<QVariantList> PrepareListData(ModelStruct &modelStruct, ModelSettings& settings);



    bool m_isConnected = false;

    SenderDataDialog* m_senderDataDialog;

    DataClass* m_dataClass;

    AskToUseSettingsDialog* m_askDialog = nullptr;

    SqlDataClassThread* m_sqlThread;

    QSqlDatabase m_dataBase;

};

#endif // SQLDATABSEHANDLER_HPP
