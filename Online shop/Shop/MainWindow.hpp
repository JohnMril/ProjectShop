#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtWidgets>

#include "Parser/Parser.hpp"
#include "Parser/ParserHolderWidget.hpp"
#include "ModelHandler.hpp"
#include "DataClass/DataClass.hpp"

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
    void on_pushButton_clicked();

    void on_actionSort_triggered();

    void on_actionRemove_row_triggered();


    void on_actionAdd_row_triggered();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void AddNewModelViewElement();


private:
    Ui::MainWindow *ui;
    ModelHandler m_modelHandler;
    Parser m_parser;

    DataClass m_dataClass;

    ParserHolderWidget* m_parserHolder;

    QSortFilterProxyModel *m_currenttProxyModel = nullptr;
};
#endif // MAINWINDOW_HPP
