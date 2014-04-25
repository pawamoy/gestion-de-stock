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

    int index = color_box->GetIndex( (std::string)ac->GetColorName().toUtf8().constData() );
    if ( index != -1 )
    { // -1 for not found
       color_box->setCurrentIndex(index);
    }

    index = size_box->GetIndex( ac->GetSizeInt() );
    std::cout << "index : " << index << std::endl;
    if ( index != -1 )
    { // -1 for not found
       size_box->setCurrentIndex(index);
    }

    index = category_box->GetIndex( (std::string)ac->GetCategoryName().toUtf8().constData() );
    std::cout << "index : " << index << std::endl;
    if ( index != -1 )
    { // -1 for not found
       category_box->setCurrentIndex(index);
    }

    std::cout << "type : " << ac->GetTypeInt() << std::endl;

    ui->field_categorie->addWidget(category_box);
    ui->field_type->addWidget(type_box);
    ui->field_taille->addWidget(size_box);
    ui->field_couleur->addWidget(color_box);

    ui->refca->setValue(ac->GetCategoryInt());
    ui->reft->setValue(atoi(ac->GetTypeString().toUtf8().constData()));
    ui->refm->setValue(ac->GetModelInt());
    ui->refs->setValue(ac->GetSizeInt());
    ui->refco->setValue(ac->GetColorInt());

    ui->model_spin->setValue(ac->GetModelInt());
    ui->qty_spin->setValue(ac->GetQuantity());
    ui->achat_spin->setValue(ac->GetBuyPrice());
    ui->vente_spin->setValue(ac->GetSellPrice());
    ui->rabais_spin->setValue(ac->GetDiscountPercent());

    QDate date(ac->GetDeliveryDate().year(), ac->GetDeliveryDate().month(), ac->GetDeliveryDate().day());
    ui->date_edit->setDate(date);
}

modifStock::~modifStock()
{
    delete ui;
}

void modifStock::changeCat()
{
    ui->field_type->removeWidget(type_box);
    type_box = new ComboBoxType(this, category_box->currentIndex(), 0);
    ui->field_type->addWidget(type_box);
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
