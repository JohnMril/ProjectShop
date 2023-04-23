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

class RequestClassHandler : public QWidget
{
    Q_OBJECT

public:
    explicit RequestClassHandler(QWidget *parent = nullptr);
    ~RequestClassHandler();

signals:
    void DataAccepted(const int &);

private slots:
    void on_pushButtonGetAll_clicked();
    void emitSignal(const int& enumApi);

private:


    void FillWidgets();

    void GetAllData();

    QMap<API, RequestClass*> m_mapSubWidgets;
    QGridLayout* m_gridList;

    QString m_pathToDir;

    Ui::RawDataHandler *ui;
};

#endif // RAWDATAHANDLER_HPP
