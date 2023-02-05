#include "ParsingDialog.hpp"
#include "ui_ParsingDialog.h"

ParsingDialog::ParsingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParsingDialog)
{
    ui->setupUi(this);
}

ParsingDialog::~ParsingDialog()
{
    delete ui;
}
