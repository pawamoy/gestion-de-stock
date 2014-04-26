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

void ajoutStock::changeCat()
{
    ui->refca->setValue(GetCategory());

    delete type_box;
    type_box = new ComboBoxType(this, GetCategory(), GetRefType());
    ui->field_type->addWidget(type_box);

    connect(type_box, SIGNAL(currentIndexChanged(int)), this, SLOT(changeType()));
}

void ajoutStock::changeType()
{
    int nc = GetCategory();
    int nt = GetType();

    bool set = false;

    if (nt != NR)
    {
        switch (nc)
        {
        case INTERVETEMENT:
            if (nt < END_TYPE1) set = true;
            break;

        case VETEMENT1:
        case VETEMENT2:
        case VETEMENT3:
        case VETEMENT4:
            if (nt < END_TYPE2) set = true;
            break;

        case SURVETEMENT1:
        case SURVETEMENT2:
        case SURVETEMENT3:
            if (nt < END_TYPE3) set = true;
            break;

        case ENSEMBLE:
            if (nt < END_TYPE4) set = true;
            break;

        case SOUSVETEMENT:
        default:
            if (nt < END_TYPE0) set = true;
            break;
        }
    }

    if (set == true)
        ui->reft->setValue(nt);
    else
        ui->reft->setValue(0);
}

void ajoutStock::changeSize()
{
    ui->refs->setValue(GetSize());
}

void ajoutStock::changeColor()
{
    ui->refco->setValue(GetColor());
}

void ajoutStock::changeModele()
{
    ui->refm->setValue(GetModel());
}

void ajoutStock::changeRefCat()
{
    category_box->setCurrentIndex(GetRefCategory());
}

void ajoutStock::changeRefType()
{
    type_box->SetSelection(GetRefCategory(),GetRefType());
}

void ajoutStock::changeRefSize()
{
    size_box->setCurrentIndex(GetRefSize());
}

void ajoutStock::changeRefColor()
{
    color_box->setCurrentIndex(GetRefColor());
}

void ajoutStock::changeRefModele()
{
    ui->model_spin->setValue(GetRefModel());
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

    StockArticle sa((Ref){ca,ty,mo,si,co},NR,bp,sp,di,da);
    StockArticle *nsa = stock->GetArticle(sa);

    if (nsa != NULL)
        stock->Add(nsa, qt);
    else
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
