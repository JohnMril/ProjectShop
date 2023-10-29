#ifndef SELECTERPARSINGFILESDIALOG_HPP
#define SELECTERPARSINGFILESDIALOG_HPP

#include <QDialog>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QGridLayout>
#include <QTimer>
#include <QEventLoop>

#include "FileSelector.hpp"
#include "RequsterClass/RequestClassHandler.hpp"
#include "Common/EnumerationClass.hpp"

namespace Ui {
class SelecterParsingFilesDialog;
}

class SelecterParsingFilesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelecterParsingFilesDialog(QWidget *parent = nullptr);
    ~SelecterParsingFilesDialog();

    void acceptSignal(QString text);

    void LoadAllData();

signals:
    void sourceDataSelected(int);
    void allDataLoaded();

private slots:
    void on_pushButton_clicked();

    void on_loadPushButton_clicked();

    void timeOutTimer();

private:
    Ui::SelecterParsingFilesDialog *ui;

    RequestClassHandler* m_requstHandler;

    QDir m_currentDir;
    QString m_pathToDir;
    QFileInfoList m_currentFileList;
    QGridLayout* m_gridLayout;

    QMap<API, QString> m_enumMap;

    QTimer* m_timer;
    int m_minute =0;


    QVector<FileSelector*> m_fileSelectorVec;
    QEventLoop* m_eventLoop;
};

#endif // SELECTERPARSINGFILESDIALOG_HPP
