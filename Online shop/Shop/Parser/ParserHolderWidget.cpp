#include "ParserHolderWidget.hpp"

ParserHolderWidget::ParserHolderWidget(QWidget *parent) : QWidget(parent)
{

}



void ParserHolderWidget::AddNewFile()
{
    QString pathString = EmitFileFinder();

    if(pathString.isNull())
    {
        return;
    }

    if (!ParseByFilePath(pathString))
    {
        CallErorrMessageBox("File can't be read!!!", "file error");
        return;
    }

    m_parserDialog = new ParsingDialog(m_parser.GetModelStruct(),this);
    m_parserDialog->show();

}



QString ParserHolderWidget::EmitFileFinder()
{

    QString filter = "All File (*.*);; Text File (*.txt);; XML File (*.xml)";
    QString file_name = QFileDialog::getOpenFileName(this, "Open file", "C://",filter);

    return file_name;
}



bool ParserHolderWidget::ParseByFilePath(QString path)
{
    //TODO Добавить парсинг в зависимости от типа файла.
    return m_parser.ParsingFileToModel(path);
}



void ParserHolderWidget::CallErorrMessageBox(QString text, QString title)
{
    //TODO переделать под messageBox

    qDebug() << text<< title;
}
