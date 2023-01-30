#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menubar->setEnabled(false);
    ui->tableView->setModel(m_modelHandler.GetPlacesModels());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString filter = "All File (*.*);; Text File (*.txt);; XML File (*.xml)";
    QString file_name = QFileDialog::getOpenFileName(this, "Open file", "C://",filter);

    m_parser.ParsingFileToModel(file_name);

    m_modelHandler.CreateModel(m_parser.GetLastModel());

    m_currenttProxyModel = m_modelHandler.GetMapOfProxyModels().last();

    ui->tableView->setModel(m_modelHandler.GetPlacesModels());

    ui->tableView_2->setModel(m_currenttProxyModel);

    ui->comboBox->setModel(m_modelHandler.GetPlacesModels());

    ui->menubar->setEnabled(true);
}



void MainWindow::on_actionSort_triggered()
{

    m_currenttProxyModel->sort( ui->tableView_2->selectionModel()->currentIndex().column()
                                , Qt::AscendingOrder);
}



void MainWindow::on_actionRemove_row_triggered()
{
    m_currenttProxyModel->removeRow(ui->tableView_2->selectionModel()->currentIndex().row());
//    m_currenttProxyModel->mapToSource(ui->tableView_2->selectionModel()->currentIndex());
}



void MainWindow::on_actionAdd_row_triggered()
{
    m_currenttProxyModel->insertRow(ui->tableView_2->selectionModel()->currentIndex().row());
}



void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(m_modelHandler.GetMapOfProxyModels().contains(arg1))
    {
        m_currenttProxyModel = m_modelHandler.GetMapOfProxyModels().value(arg1);
        ui->tableView_2->setModel(m_modelHandler.GetMapOfProxyModels().value(arg1));
    }

}
