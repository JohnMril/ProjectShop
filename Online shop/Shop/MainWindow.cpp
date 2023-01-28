#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menubar->setEnabled(false);

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

    m_modelHandler.CreateModel(m_parser.GetVecModelStruct().first());

    m_proxyModel = new QSortFilterProxyModel(this);
    m_proxyModel->setSourceModel(m_modelHandler.GetMainShop());
    ui->tableView->setModel(m_modelHandler.GetPlacesModels());

    ui->tableView_2->setModel(m_proxyModel);

    ui->menubar->setEnabled(true);
}



void MainWindow::on_actionSort_triggered()
{

    m_proxyModel->sort( ui->tableView_2->selectionModel()->currentIndex().column()
                        , Qt::AscendingOrder);
}



void MainWindow::on_actionRemove_row_triggered()
{
    m_proxyModel->removeRow(ui->tableView_2->selectionModel()->currentIndex().row());
}



void MainWindow::on_actionAdd_row_triggered()
{
    m_proxyModel->insertRow(ui->tableView_2->selectionModel()->currentIndex().row());
}
