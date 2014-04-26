#include "ajoutvente.h"
#include "ui_ajoutvente.h"

ajoutVente::ajoutVente(QWidget *parent, Stock* st, Sells* se) :
    QDialog(parent),
    ui(new Ui::ajoutVente)
{
    ui->setupUi(this);
    stock = st;
    sells = se;

    ui->date_vente->setDate(QDate::currentDate());

    // ligne suivantes lors de la création d'une vente DEPUIS une ligne du stock :)
//    ui->refca->setValue(ac->GetCategoryInt());
//    ui->reft->setValue(ac->GetTypeInt());
//    ui->refm->setValue(ac->GetModelInt());
//    ui->refs->setValue(ac->GetSizeInt());
//    ui->refco->setValue(ac->GetColorInt());

//    ui->quantite_spin->setValue(ac->GetQuantity());
//    ui->achat_spin->setValue(ac->GetBuyPrice());
//    ui->vente_spin->setValue(ac->GetSellPrice());
//    ui->rabais_spin->setValue(ac->GetDiscountPercent());

//    ui->date_edit->setDate(ac->GetDeliveryDate());
}

ajoutVente::~ajoutVente()
{
    delete ui;
}

void ajoutVente::on_annuler_clicked()
{
    this->close();
}

void ajoutVente::on_valider_clicked()
{
//    int ca = GetRefCategory();
//    int ty = GetRefType();
//    int mo = GetRefModel();
//    int si = GetRefSize();
//    int co = GetRefColor();
//    int qt = GetQuantity();
//    float bp = GetBuyPrice();
//    float sp = GetSellPrice();
//    int di = GetDiscount();
//    QDate da = GetDelivery();

    //Ref modifiedRef = {ca,ty,mo,si,co};
    //StockArticle modified (modifiedRef, qt, bp, sp, di, da);
    //stock->Modify(article,modified);

    this->close();
}

int ajoutVente::GetRefCategory()
{
    return ui->refca->value();
}

int ajoutVente::GetRefType()
{
    return ui->reft->value();
}

int ajoutVente::GetRefModel()
{
    return ui->refm->value();
}

int ajoutVente::GetRefSize()
{
    return ui->refs->value();
}

int ajoutVente::GetRefColor()
{
    return ui->refco->value();
}

int ajoutVente::GetQuantity()
{
    return ui->quantite_spin->value();
}

float ajoutVente::GetBuyPrice()
{
    return ui->achat_spin->value();
}

float ajoutVente::GetSellPrice()
{
    return ui->vente_spin->value();
}

int ajoutVente::GetDiscount()
{
    return ui->rabais_spin->value();
}

QDate ajoutVente::GetDelivery()
{
    return ui->date_livraison->date();
}

QDate ajoutVente::GetSellDate()
{
    return ui->date_vente->date();
}

