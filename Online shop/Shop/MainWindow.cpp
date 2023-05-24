#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_settingHandler = new SettingHandler(&m_dataClass, this);

    m_sqlDataBaseHandler = new SqlDatabaseHandler(&m_dataClass, this);
    m_sqlAuthDialog = new AuthorizationDialog(m_sqlDataBaseHandler, this);
    m_sqlDataBaseHandler->hide();

    connect(m_sqlDataBaseHandler, &SqlDatabaseHandler::NeedToConnect, this, &MainWindow::EmitAuthSql);

    m_selectorFileDialog = new SelecterParsingFilesDialog(this);
    m_selectorFileDialog->hide();

    m_parserHolder = new ParserHolderWidget(this);
    m_parserHolder->SetDataClass(&m_dataClass);
    m_modelHandler.SetDataClass(&m_dataClass);

    ui->modelsView->setModel(m_modelHandler.GetPlacesModels());


    connect(&m_modelHandler, &ModelHandler::CreatedNewModel, this, &MainWindow::AddNewModelViewElement);

    connect(m_selectorFileDialog, &SelecterParsingFilesDialog::sourceDataSelected, m_parserHolder, &ParserHolderWidget::DataLoaded);

    connect(m_parserHolder, &ParserHolderWidget::NewModelLoaded, &m_modelHandler, &ModelHandler::CreateModelByString);

    //setting
    connect(&m_dataClass, &DataClass::NewSettingAdded, m_settingHandler, &SettingHandler::SettingSave);

    m_settingHandler->SettingDownload();
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



void MainWindow::AddNewModelViewElement(const QString& modelName)
{
    ui->comboBox->setModel(m_modelHandler.GetPlacesModels());

    QMap<QString, QSortFilterProxyModel*> tmpMap = m_modelHandler.GetMapOfProxyModels();
    if(tmpMap.contains(modelName))
    {
        ui->currentModelView->setModel(tmpMap.value(modelName));

        PushButtonSender* button = new PushButtonSender(modelName, this);
        connect(button, &PushButtonSender::Clicked, this, &MainWindow::PreapareToSendData);

        ui->modelsView->setIndexWidget(m_modelHandler.GetIndexOfPlacesModelByName(modelName), button);

    }
}

void MainWindow::EmitAuthSql()
{
    m_sqlAuthDialog->show();
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



void MainWindow::on_editViewPushButton_clicked()
{
    //TODO сделать сообщение что модели нет
    if(ui->currentModelView->model() == nullptr)
    {
        return;
    }
    m_viewEditorDialog = new ViewEditorDialog(ui->currentModelView, this);
    m_viewEditorDialog->show();
}

void MainWindow::PreapareToSendData(QString name)
{
    qDebug()<<"Pressed" <<name;
    m_sqlDataBaseHandler->PrepareToSend(name);
}
