#ifndef RAWDATAHANDLER_HPP
#define RAWDATAHANDLER_HPP

#include <QWidget>
#include <QDir>
#include <QMap>
#include <QGridLayout>
#include "RequestForSite.hpp"

namespace Ui {
class RawDataHandler;
}

class RequstClassHandler : public QWidget
{
    Q_OBJECT

public:
    explicit RequstClassHandler(QWidget *parent = nullptr);
    ~RequstClassHandler();

signals:
    void DataAccepted(const int &);

private slots:
    void on_pushButtonGetAll_clicked();

private:
    void FillWidgets();

    void GetAllData();

    QMap<API, RequestClass*> m_mapSubWidgets;
    QGridLayout* m_gridList;

    QString m_pathToDir;

    Ui::RawDataHandler *ui;



};

#endif // RAWDATAHANDLER_HPP
