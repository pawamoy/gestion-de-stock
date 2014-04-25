#include "modifstock.h"
#include "ui_modifstock.h"

modifStock::modifStock(QWidget *parent, Stock *st, StockArticle* ac) :
    QDialog(parent),
    ui(new Ui::modifStock)
{
    ui->setupUi(this);

    stock = st;

    article = ac;

    std::cout << ac->GetReferenceString().toUtf8().constData() << std::endl;

    category_box = new ComboBoxCategory(this, 0);
    type_box = new ComboBoxType(this, 0, 0);
    size_box = new ComboBoxSize(this, 0);
    color_box = new ComboBoxColor(this, 0);

    //ui->refca->setValue(ac->GetReference);
    //ui->refca->setValue(ac->GetReferenceInt()() - ac->GetReferenceInt()/10000000);

    ui->field_categorie->addWidget(category_box);
    ui->field_type->addWidget(type_box);
    ui->field_taille->addWidget(size_box);
    ui->field_couleur->addWidget(color_box);
}

modifStock::~modifStock()
{
    delete ui;
}

void modifStock::on_annuler_clicked()
{
    this->close();
}

void modifStock::on_valider_clicked()
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

int modifStock::GetRefCategory()
{
    return ui->refca->value();
}

int modifStock::GetCategory()
{
    return category_box->currentIndex();
}

int modifStock::GetRefType()
{
    return ui->reft->value();
}

int modifStock::GetType()
{
    return type_box->currentIndex();
}

int modifStock::GetRefModel()
{
    return ui->refm->value();
}

int modifStock::GetModel()
{
    return ui->model_spin->value();
}

int modifStock::GetRefSize()
{
    return ui->refs->value();
}

int modifStock::GetSize()
{
    return size_box->currentIndex();
}

int modifStock::GetRefColor()
{
    return ui->refco->value();
}

int modifStock::GetColor()
{
    return color_box->currentIndex();
}

int modifStock::GetQuantity()
{
    return ui->qty_spin->value();
}

float modifStock::GetBuyPrice()
{
    return ui->achat_spin->value();
}

float modifStock::GetSellPrice()
{
    return ui->vente_spin->value();
}

int modifStock::GetDiscount()
{
    return ui->rabais_spin->value();
}

QDate modifStock::GetDelivery()
{
    return ui->date_edit->date();
}
