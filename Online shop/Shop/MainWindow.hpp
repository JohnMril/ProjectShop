#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtWidgets>

#include "Parser/Parser.hpp"
#include "Parser/ParserHolderWidget.hpp"
#include "ModelHandler.hpp"
#include "DataClass/DataClass.hpp"
#include "DataClass/SqlDataBase.hpp"
#include "SortingsDialog/SortingDialog.hpp"
#include "RequsterClass/RequestClassHandler.hpp"
#include "Parser/SelecterParsingFilesDialog.hpp"

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

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void AddNewModelViewElement();


    void on_actionAdd_row_2_triggered();

    void on_actionRemove_row_2_triggered();

    void on_actionSort_column_triggered();

    void on_actionFinding_by_name_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    ModelHandler m_modelHandler;
    Parser m_parser;

    DataClass m_dataClass;

    ParserHolderWidget* m_parserHolder;

    SqlDataBase m_sqlDataBase;

    QSortFilterProxyModel *m_currenttProxyModel = nullptr;

    SortingDialog* m_sortingDialog = nullptr;

    SelecterParsingFilesDialog* m_selectorFileDialog = nullptr;
};
#endif // MAINWINDOW_HPP
