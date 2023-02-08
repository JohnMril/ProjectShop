#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menubar->setEnabled(false);
    ui->modelsView->setModel(m_modelHandler.GetPlacesModels());


    m_parserHolder = new ParserHolderWidget(this);
    m_parserHolder->SetDataClass(&m_dataClass);
    m_modelHandler.SetDataClass(&m_dataClass);

    connect(m_parserHolder, &ParserHolderWidget::NewModelStructHasCreated, &m_modelHandler, &ModelHandler::CreateNewModelFromDataClass);

    connect(&m_modelHandler, &ModelHandler::CreatedNewModel, this, &MainWindow::AddNewModelViewElement);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    m_parserHolder->AddNewFile();

    //TODO Убрать перенести в вверх.
    //    QString filter = "All File (*.*);; Text File (*.txt);; XML File (*.xml)";
    //    QString file_name = QFileDialog::getOpenFileName(this, "Open file", "C://",filter);

    //    if(file_name.isNull())
    //    {
    //        qDebug()<<"File not chosen";
    //        return;
    //    }

    //    m_parser.ParsingFileToModel(file_name);

    //    m_modelHandler.CreateModel(m_parser.GetModelStruct());

    //    m_currenttProxyModel = m_modelHandler.GetMapOfProxyModels().last();

    //    ui->tableView->setModel(m_modelHandler.GetPlacesModels());

    //    ui->tableView_2->setModel(m_currenttProxyModel);

    //    ui->comboBox->setModel(m_modelHandler.GetPlacesModels());

    //    ui->menubar->setEnabled(true);
}



void MainWindow::on_actionSort_triggered()
{

    m_currenttProxyModel->sort( ui->currentModelView->selectionModel()->currentIndex().column()
                                , Qt::AscendingOrder);
}



void MainWindow::on_actionRemove_row_triggered()
{
    m_currenttProxyModel->removeRow(ui->currentModelView->selectionModel()->currentIndex().row());
}



void MainWindow::on_actionAdd_row_triggered()
{
    m_currenttProxyModel->insertRow(ui->currentModelView->selectionModel()->currentIndex().row());
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

    if(!ui->menubar->isEnabled())
    {
            ui->menubar->setEnabled(true);
            ui->comboBox->setView(ui->modelsView);
    }


    ui->comboBox->setCurrentIndex(ui->comboBox->model()->rowCount());

}
