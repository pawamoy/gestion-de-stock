#include "vente.h"
#include "ui_vente.h"

vente::vente(QWidget *parent,  StockArticle* ac) :
    QDialog(parent),
    ui(new Ui::vente)
{
    ui->setupUi(this);

    std::cout << ac->GetReferenceString().toUtf8().constData() << std::endl;

    std::string text = "";
    text = text + "Vente en cours de l'article " + ac->GetReferenceString().toUtf8().constData();
    ui->label->setText(QString(text.c_str()));


    text = "";
    text = text + "Quantité à vendre (maximum : " + ac->GetQuantityString().toUtf8().constData() + ") : ";
    ui->label_2->setText(QString(text.c_str()));
}

vente::~vente()
{
    delete ui;
}
