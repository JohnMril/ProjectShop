#ifndef REQUESTCLASSHANDLER_HPP
#define REQUESTCLASSHANDLER_HPP

#include <QDialog>
#include <QDialog>
#include <QDir>
#include <QMap>
#include <QGridLayout>
#include <QFileInfoList>
#include "RequestClass.hpp"

namespace Ui {
class RequestClassHandler;
}

class RequestClassHandler : public QDialog
{
    Q_OBJECT

public:
    explicit RequestClassHandler(QWidget *parent = nullptr);
    ~RequestClassHandler();
        void GetAllData();


private slots:

    void on_pushButtonGetAll_clicked();

private:

    void FillWidgets();



    QVector<RequestClass*> m_widgetVec;
    QGridLayout* m_gridList;

    QString m_pathToDir;
    QDir    m_currentDir;

    Ui::RequestClassHandler *ui;
};

#endif // REQUESTCLASSHANDLER_HPP
