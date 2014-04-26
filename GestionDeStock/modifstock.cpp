#include "modifstock.h"
#include "ui_modifstock.h"

modifStock::modifStock(QWidget *parent, Stock *st, StockArticle* ac) :
    QDialog(parent),
    ui(new Ui::modifStock)
{
    ui->setupUi(this);
    stock = st;
    article = ac;

    category_box = new ComboBoxCategory(this, 0);
    type_box = new ComboBoxType(this, 0, 0);
    size_box = new ComboBoxSize(this, 0);
    color_box = new ComboBoxColor(this, 0);

    connect(category_box, SIGNAL(currentIndexChanged(int)), this, SLOT(changeCat()));
    connect(type_box, SIGNAL(currentIndexChanged(int)), this, SLOT(changeType()));
    connect(size_box, SIGNAL(currentIndexChanged(int)), this, SLOT(changeSize()));
    connect(color_box, SIGNAL(currentIndexChanged(int)), this, SLOT(changeColor()));
    connect(ui->model_spin, SIGNAL(valueChanged(int)), this, SLOT(changeModele()));

    connect(ui->refca, SIGNAL(valueChanged(int)), this, SLOT(changeRefCat()));
    connect(ui->reft, SIGNAL(valueChanged(int)), this, SLOT(changeRefType()));
    connect(ui->refs, SIGNAL(valueChanged(int)), this, SLOT(changeRefSize()));
    connect(ui->refco, SIGNAL(valueChanged(int)), this, SLOT(changeRefColor()));
    connect(ui->refm, SIGNAL(valueChanged(int)), this, SLOT(changeRefModele()));

    category_box->SetSelection(ac->GetCategoryInt());
    type_box->SetSelection(ac->GetCategoryInt(), ac->GetTypeInt());
    size_box->SetSelection(ac->GetSizeInt());
    color_box->SetSelection(ac->GetColorInt());

    ui->field_categorie->addWidget(category_box);
    ui->field_type->addWidget(type_box);
    ui->field_taille->addWidget(size_box);
    ui->field_couleur->addWidget(color_box);

    ui->refca->setValue(ac->GetCategoryInt());
    ui->reft->setValue(ac->GetTypeInt());
    ui->refm->setValue(ac->GetModelInt());
    ui->refs->setValue(ac->GetSizeInt());
    ui->refco->setValue(ac->GetColorInt());

    ui->model_spin->setValue(ac->GetModelInt());
    ui->qty_spin->setValue(ac->GetQuantity());
    ui->achat_spin->setValue(ac->GetBuyPrice());
    ui->vente_spin->setValue(ac->GetSellPrice());
    ui->rabais_spin->setValue(ac->GetDiscountPercent());

    ui->date_edit->setDate(ac->GetDeliveryDate());
}

modifStock::~modifStock()
{
    delete ui;
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
    return size_box->GetIndex(size_box->currentIndex());
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

    Ref modifiedRef = {ca,ty,mo,si,co};
    StockArticle modified (modifiedRef, qt, bp, sp, di, da);
    stock->Modify(article,modified);

    this->close();
}









void modifStock::changeCat()
{
    ui->refca->setValue(GetCategory());

    delete type_box;
    type_box = new ComboBoxType(this, GetCategory(), GetRefType());
    ui->field_type->addWidget(type_box);

    connect(type_box, SIGNAL(currentIndexChanged(int)), this, SLOT(changeType()));
}

void modifStock::changeType()
{
    ui->reft->setValue(GetType());
}

void modifStock::changeSize()
{
    ui->refs->setValue(GetSize());
}

void modifStock::changeColor()
{
    ui->refco->setValue(GetColor());
}

void modifStock::changeModele()
{
    ui->refm->setValue(GetModel());
}

void modifStock::changeRefCat()
{
    category_box->SetSelection(GetRefCategory());
}

void modifStock::changeRefType()
{
    type_box->SetSelection(GetRefCategory(),GetRefType());
}

void modifStock::changeRefSize()
{
    size_box->SetSelection(GetRefSize());
}

void modifStock::changeRefColor()
{
    color_box->SetSelection(GetRefColor());
}

void modifStock::changeRefModele()
{
    ui->model_spin->setValue(GetRefModel());
}
