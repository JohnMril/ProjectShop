#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_settingHandler = new SettingHandler(&m_dataClass, this);    
    m_settingHandler->SettingDownload();

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

    this->resize(525, 350);

}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::AddNewModelViewElement(const QString& modelName)
{
//    ui->comboBox->setModel(m_modelHandler.GetPlacesModels());

//    QMap<QString, QSortFilterProxyModel*> tmpMap = m_modelHandler.GetMapOfProxyModels();
//    if(tmpMap.contains(modelName))
        if(true)
    {
//        ui->currentModelView->setModel(tmpMap.value(modelName));

        PushButtonSender* button = new PushButtonSender(modelName, this);
        connect(button, &PushButtonSender::Clicked, this, &MainWindow::PreapareToSendData);
        ui->modelsView->setIndexWidget(m_modelHandler.GetIndexOfPlacesModelByName(modelName), button);

        PushButtonSender* button0 = new PushButtonSender(modelName, this);
        connect(button0, &PushButtonSender::Clicked, this, &MainWindow::EmitModelViewDialog);
        ui->modelsView->setIndexWidget(m_modelHandler.GetIndexOfPlacesModelByName(modelName, 3), button0);


        ui->modelsView->resizeColumnsToContents();


    }
}

void MainWindow::EmitAuthSql()
{
    m_sqlAuthDialog->show();
}



void MainWindow::on_pushButton_3_clicked()
{
    m_selectorFileDialog->show();
}



void MainWindow::EmitModelViewDialog(QString modelName)
{

    QStandardItemModel* model = m_modelHandler.CreateTmpMOdel(modelName);
    if(model != nullptr)
    {

        m_viewDialog = new ModelViewDialog(model, this);
        m_viewDialog->show();
    }
}

void MainWindow::PreapareToSendData(QString name)
{
    qDebug()<<"Pressed" <<name;
    m_sqlDataBaseHandler->PrepareToSend(name);
}
