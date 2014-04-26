#include "vente.h"
#include "ui_vente.h"

vente::vente(QWidget *parent,  Stock *st, Sells *se, StockArticle* ac) :
    QDialog(parent),
    ui(new Ui::vente)
{
    ui->setupUi(this);

    s = st;
    this->se = se;
    a = ac;

    std::cout << ac->GetReferenceString().toUtf8().constData() << std::endl;

    std::string text = "";
    text = text + "Vente en cours de l'article " + ac->GetReferenceString().toUtf8().constData();
    ui->label->setText(QString(text.c_str()));


    text = "";
    text = text + "Quantité à vendre (maximum : " + ac->GetQuantityString().toUtf8().constData() + ") : ";
    ui->label_2->setText(QString(text.c_str()));

    ui->spinBox->setMaximum(ac->GetQuantity());
}

vente::~vente()
{
    delete ui;
}

void vente::on_valider_clicked()
{
    std::cout << ui->spinBox->value() << std::endl;

    s->ToSell(a,ui->spinBox->value());
    se->New(a->GetReferenceRef(),ui->spinBox->value(),a->GetBuyPrice(),a->GetSellPrice(), a->GetDiscountPercent(), a->GetDeliveryDate());

    this->close();
}

void vente::on_annuler_clicked()
{
    this->close();
}
