#include "SelecterParsingFilesDialog.hpp"
#include "ui_SelecterParsingFilesDialog.h"

SelecterParsingFilesDialog::SelecterParsingFilesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelecterParsingFilesDialog)
{
    ui->setupUi(this);

    m_requstHandler = new RequestClassHandler(this);
    m_requstHandler->hide();

    m_currentDir.setPath(QDir::currentPath());
    m_currentDir.cdUp();
    if(!m_currentDir.cd("rawData"))
    {
        qDebug() << "cant found rawData dir";
    }
    m_pathToDir = m_currentDir.path();

    m_gridLayout = new QGridLayout(ui->filesToLoad);

    m_enumMap.insert(API::LANIT, "LanitProducts.txt");
    m_enumMap.insert(API::ASBIS, "asbisProducts.txt");



    on_pushButton_clicked();
}



SelecterParsingFilesDialog::~SelecterParsingFilesDialog()
{
    delete ui;
}



void SelecterParsingFilesDialog::acceptSignal(QString text)
{
    qDebug() <<"fileName "<< text;

    emit sourceDataSelected(m_enumMap.key(text));

}



void SelecterParsingFilesDialog::on_pushButton_clicked()
{
    for (auto widget : m_fileSelectorVec)
    {
        delete widget;
    }
    m_fileSelectorVec.clear();

    m_currentDir.setPath(m_pathToDir);
    m_currentFileList = m_currentDir.entryInfoList();

    FileSelector* tmpWidget;


    for (auto file : m_currentFileList)
    {
        if(file.fileName().contains("Products.txt"))
        {
            tmpWidget = new FileSelector(file, this);
            connect(tmpWidget, &FileSelector::fileSelected, this, &SelecterParsingFilesDialog::acceptSignal);

            m_gridLayout->addWidget(tmpWidget);
            m_fileSelectorVec.push_back(tmpWidget);
        }
    }
}




void SelecterParsingFilesDialog::on_loadPushButton_clicked()
{
    m_requstHandler->show();
}
