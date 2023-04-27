#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    m_selectorFileDialog = new SelecterParsingFilesDialog(this);
    m_selectorFileDialog->hide();

    m_parserHolder = new ParserHolderWidget(this);
    m_parserHolder->SetDataClass(&m_dataClass);
    m_modelHandler.SetDataClass(&m_dataClass);

    ui->modelsView->setModel(m_modelHandler.GetPlacesModels());

    connect(m_parserHolder, &ParserHolderWidget::NewModelStructHasCreated, &m_modelHandler, &ModelHandler::CreateNewModelFromDataClass);

    connect(&m_modelHandler, &ModelHandler::CreatedNewModel, this, &MainWindow::AddNewModelViewElement);

    connect(m_selectorFileDialog, &SelecterParsingFilesDialog::sourceDataSelected, m_parserHolder, &ParserHolderWidget::DataLoaded);



}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(m_modelHandler.GetMapOfProxyModels().contains(arg1))
    {
        m_currenttProxyModel = m_modelHandler.GetMapOfProxyModels().value(arg1);
        ui->currentModelView->setModel(m_modelHandler.GetMapOfProxyModels().value(arg1));
    }
}



void MainWindow::AddNewModelViewElement()
{
    ui->comboBox->setModel(m_modelHandler.GetPlacesModels());
}



void MainWindow::on_actionAdd_row_2_triggered()
{
    if(m_currenttProxyModel)
        m_currenttProxyModel->insertRow(ui->currentModelView->selectionModel()->currentIndex().row());
}



void MainWindow::on_actionRemove_row_2_triggered()
{
    if(m_currenttProxyModel)
        m_currenttProxyModel->removeRow(ui->currentModelView->selectionModel()->currentIndex().row());
}



void MainWindow::on_actionSort_column_triggered()
{

    if(m_currenttProxyModel)
        m_currenttProxyModel->sort( ui->currentModelView->selectionModel()->currentIndex().column()
                                    , Qt::AscendingOrder);

}



void MainWindow::on_actionFinding_by_name_triggered()
{
    if(!m_sortingDialog)
    {
        m_sortingDialog = new SortingDialog(this);
        m_sortingDialog->SetProxyModel(m_currenttProxyModel);
        m_sortingDialog->show();

    }
}



void MainWindow::on_pushButton_2_clicked()
{
    m_parserHolder->DataLoaded(API::LANIT);
}



void MainWindow::on_pushButton_3_clicked()
{
    m_selectorFileDialog->show();
}
