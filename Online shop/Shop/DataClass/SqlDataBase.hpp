#ifndef SQLDATABASE_HPP
#define SQLDATABASE_HPP

#include <QObject>
#include <QtSql>
#include <QDebug>
#include <QSqlTableModel>


class SqlDataBase : public QObject
{
    Q_OBJECT
public:
    explicit SqlDataBase(QObject *parent = nullptr);


    bool MakeConection(QString serverAdres, QString dataBaseName, QString userName, QString password);

    void InsertItems(QVector<QVariantList> itemList);



signals:

private:

    QSqlDatabase m_dataBase;

};

#endif // SQLDATABASE_HPP
