#include "RequestClassHandler.hpp"
#include "ui_RequestClassHandler.h"

RequestClassHandler::RequestClassHandler(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RequestClassHandler)
{
    ui->setupUi(this);

    m_currentDir.setPath(QDir::currentPath());
    m_currentDir.cdUp();
    m_currentDir.cd("rawData");
    m_pathToDir = m_currentDir.path();
    FillWidgets();
}

RequestClassHandler::~RequestClassHandler()
{
    delete ui;
}



void RequestClassHandler::FillWidgets()
{
    m_gridList = new QGridLayout(ui->siteList);
    ui->siteList->setLayout(m_gridList);
    RequestClass* tmpWidget;

    QFileInfoList fileList = m_currentDir.entryInfoList();

    for (auto fileInfo : fileList)
    {
        if(fileInfo.fileName().contains(".bat"))
        {
            tmpWidget = new RequestClass(fileInfo);
            m_widgetVec.push_back(tmpWidget);
            m_gridList->addWidget(tmpWidget);
        }
    }

}



void RequestClassHandler::GetAllData()
{
     for (auto widget : m_widgetVec)
     {
            widget->StartGettingData();
     }
}

void RequestClassHandler::on_pushButtonGetAll_clicked()
{
    GetAllData();
}
