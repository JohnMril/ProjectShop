#include "FileSelector.hpp"
#include "ui_FileSelector.h"

FileSelector::FileSelector(QFileInfo fileInfo,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileSelector),
    m_fileInfo(fileInfo)
{
    ui->setupUi(this);

    ui->fileNameLabel->setText(fileInfo.fileName());
    ui->changeDataLabel->setText(fileInfo.lastModified().toString());

}


FileSelector::~FileSelector()
{
    delete ui;
}

void FileSelector::on_pushButton_clicked()
{
    emit fileSelected(m_fileInfo.fileName());
}
