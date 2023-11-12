#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtWidgets>

#include "Parser/Parser.hpp"
#include "Parser/ParserHolderWidget.hpp"
#include "ModelHandler.hpp"
#include "SettingHandler.hpp"
#include "DataClass/DataClass.hpp"
#include "DataClass/SqlDataBase.hpp"
#include "SortingsDialog/SortingDialog.hpp"
#include "RequsterClass/RequestClassHandler.hpp"
#include "Parser/SelecterParsingFilesDialog.hpp"
#include "ViewEditorDialog/ViewEditorDialog.hpp"
#include "ViewEditorDialog/ModelViewDialog.hpp"
#include "SqlDataBase/SqlDatabseHandler.hpp"
#include "SqlDataBase/AuthorizationDialog.hpp"
#include "SqlDataBase/PushButtonSender.hpp"
#include "LogDialog.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void ShowMainWindow();

    void AddNewModelViewElement(const QString &modelName);

    void EmitAuthSql();


    void EmitModelViewDialog(QString modelName);





    void on_pushButton_3_clicked();


    void on_loadAllButton_clicked();

    void on_sqlScript_clicked();

private:


    void PreapareToSendData(QString name);

    Ui::MainWindow *ui;
    ModelHandler m_modelHandler;

    SettingHandler* m_settingHandler;

    Parser m_parser;

    DataClass m_dataClass;

    ParserHolderWidget* m_parserHolder;

    SqlDataBase m_sqlDataBase;

    QSortFilterProxyModel *m_currenttProxyModel = nullptr;

    SortingDialog* m_sortingDialog = nullptr;

    SelecterParsingFilesDialog* m_selectorFileDialog = nullptr;

    ViewEditorDialog* m_viewEditorDialog  = nullptr;
    ModelViewDialog* m_viewDialog = nullptr;
    //Sql
    SqlDatabaseHandler* m_sqlDataBaseHandler;
    AuthorizationDialog* m_sqlAuthDialog;

    QVector<PushButtonSender*> m_senderButtonVector;

    LogDialog* m_logDialog;



};
#endif // MAINWINDOW_HPP
