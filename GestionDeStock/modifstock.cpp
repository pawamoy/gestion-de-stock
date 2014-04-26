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

void modifStock::changeCat()
{
    std::cout << "hahahaha" << std::endl;
    ui->refca->setValue(GetCategory());

    delete type_box;
    type_box = new ComboBoxType(this, GetCategory(), GetRefType());
    ui->field_type->addWidget(type_box);
}

void modifStock::changeType()
{
    std::cout << "coucou" << std::endl;
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
