#ifndef SELECTERPARSINGFILESDIALOG_HPP
#define SELECTERPARSINGFILESDIALOG_HPP

#include <QDialog>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QGridLayout>

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

private:
    Ui::SelecterParsingFilesDialog *ui;

    RequestClassHandler* m_requstHandler;

    QDir m_currentDir;
    QString m_pathToDir;
    QFileInfoList m_currentFileList;
    QGridLayout* m_gridLayout;

    QMap<API, QString> m_enumMap;


    QVector<FileSelector*> m_fileSelectorVec;
};

#endif // SELECTERPARSINGFILESDIALOG_HPP
