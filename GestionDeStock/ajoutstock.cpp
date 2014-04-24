#include "ajoutstock.h"
#include "ui_ajoutstock.h"

ajoutStock::ajoutStock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajoutStock)
{
    ui->setupUi(this);
}

ajoutStock::~ajoutStock()
{
    delete ui;
}
