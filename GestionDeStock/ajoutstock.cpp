#include "ajoutstock.h"
#include "ui_ajoutstock.h"

ajoutStock::ajoutStock(QWidget *parent, Stock *st) :
    QDialog(parent),
    ui(new Ui::ajoutStock)
{
    ui->setupUi(this);

    stock = st;

    category_box = new ComboBoxCategory(this, 0);
    type_box = new ComboBoxType(this, 0, 0);
    size_box = new ComboBoxSize(this, 0);
    color_box = new ComboBoxColor(this, 0);

    ui->field_categorie->addWidget(category_box);
    ui->field_type->addWidget(type_box);
    ui->field_taille->addWidget(size_box);
    ui->field_couleur->addWidget(color_box);

    ui->date_edit->setDate(QDate::currentDate());
}

ajoutStock::~ajoutStock()
{
    delete ui;
}

void ajoutStock::on_annuler_clicked()
{
    this->close();
}

void ajoutStock::on_valider_clicked()
{
    int ca = GetRefCategory();
    int ty = GetRefType();
    int mo = GetRefModel();
    int si = GetRefSize();
    int co = GetRefColor();
    int qt = GetQuantity();
    float bp = GetBuyPrice();
    float sp = GetSellPrice();
    int di = GetDiscount();
    QDate da = GetDelivery();

    stock->New(new StockArticle((Ref){ca,ty,mo,si,co},qt,bp,sp,di,da));

    this->close();
}

int ajoutStock::GetRefCategory()
{
    return ui->refca->value();
}

int ajoutStock::GetCategory()
{
    return category_box->currentIndex();
}

int ajoutStock::GetRefType()
{
    return ui->reft->value();
}

int ajoutStock::GetType()
{
    return type_box->currentIndex();
}

int ajoutStock::GetRefModel()
{
    return ui->refm->value();
}

int ajoutStock::GetModel()
{
    return ui->model_spin->value();
}

int ajoutStock::GetRefSize()
{
    return ui->refs->value();
}

int ajoutStock::GetSize()
{
    return size_box->currentIndex();
}

int ajoutStock::GetRefColor()
{
    return ui->refco->value();
}

int ajoutStock::GetColor()
{
    return color_box->currentIndex();
}

int ajoutStock::GetQuantity()
{
    return ui->qty_spin->value();
}

float ajoutStock::GetBuyPrice()
{
    return ui->achat_spin->value();
}

float ajoutStock::GetSellPrice()
{
    return ui->vente_spin->value();
}

int ajoutStock::GetDiscount()
{
    return ui->rabais_spin->value();
}

QDate ajoutStock::GetDelivery()
{
    return ui->date_edit->date();
}
