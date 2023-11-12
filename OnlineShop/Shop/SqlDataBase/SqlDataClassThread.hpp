#ifndef SQLDATACLASSTHREAD_HPP
#define SQLDATACLASSTHREAD_HPP

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "DataClass/DataClass.hpp"

class SqlDataClassThread : public QObject
{
    Q_OBJECT
public:
    explicit SqlDataClassThread(DataClass* m_dataClass, QObject *parent = nullptr);

    bool MakeConnetion(QString serverAdres, QString dataBaseName, QString userName, QString password);


    QString GetLastError();

    void ThreadSoloSend(QString name);
    void ThreadAllSend();
    void RecountSend();
    void ThreadMakeConnection(QString serverAdres, QString dataBaseName, QString userName, QString password);


signals:
    void Started(QString processName);
    void Finished(QString processName);

    void EmitMessageBox(bool state);

    void SoloSendSignal(QString name);
    void SendAllSignal();
    void RecountSignal();
    void MakeConnectionSignal(QString serverAdres, QString dataBaseName, QString userName, QString password);
    void Connected(bool);

private slots:
    void SendSoloShop(QString name);
    void SendAllShops();
    void RecountAll();


private:
    bool SendDataToServer(QString name, const QVector<QVariantList>& productVec, QString& errorHandler);

    bool ClearSqlTable(QString& error);

    bool SqlScript(QString& error);

    bool SqlRecount(QString& error);

    bool IsConnnected();


    bool m_isWork = false;

    QVector<QVariantList> PrepareListData(ModelStruct &modelStruct, ModelSettings& settings);
    QThread* m_currentThread;
    QSqlDatabase m_dataBase;
    bool m_isConnected = false;
    QString m_error;
        DataClass* m_dataClass;
};

#endif // SQLDATACLASSTHREAD_HPP
