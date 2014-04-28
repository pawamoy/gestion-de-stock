#include "recherche.h"
#include "ui_recherche.h"

recherche::recherche(QWidget *parent, Stock* st) :
    QDialog(parent),
    ui(new Ui::recherche)
{
    ui->setupUi(this);

    stock = st;

    category_box = new ComboBoxCategory(this, 0);
    type_box = new ComboBoxType(this, 0, 0);
    size_box = new ComboBoxSize(this, 0);
    color_box = new ComboBoxColor(this, 0);

    Reinitialiser();

    connect(category_box, SIGNAL(currentIndexChanged(int)), this, SLOT(changedCat()));
    connect(type_box, SIGNAL(currentIndexChanged(int)), this, SLOT(changedType()));
    connect(size_box, SIGNAL(currentIndexChanged(int)), this, SLOT(changedSize()));
    connect(color_box, SIGNAL(currentIndexChanged(int)), this, SLOT(changedColor()));
    connect(ui->model_spin, SIGNAL(valueChanged(int)), this, SLOT(changedModele()));

    connect(ui->refca, SIGNAL(valueChanged(int)), this, SLOT(changedRefCat()));
    connect(ui->reft, SIGNAL(valueChanged(int)), this, SLOT(changedRefType()));
    connect(ui->refs, SIGNAL(valueChanged(int)), this, SLOT(changedRefSize()));
    connect(ui->refco, SIGNAL(valueChanged(int)), this, SLOT(changedRefColor()));
    connect(ui->refm, SIGNAL(valueChanged(int)), this, SLOT(changedRefModele()));

    connect(ui->check_buy, SIGNAL(clicked(bool)), this, SLOT(EnableBuyPrice(bool)));
    connect(ui->check_cat, SIGNAL(clicked(bool)), this, SLOT(EnableCategory(bool)));
    connect(ui->check_color, SIGNAL(clicked(bool)), this, SLOT(EnableColor(bool)));
    connect(ui->check_delivery, SIGNAL(clicked(bool)), this, SLOT(EnableDelivery(bool)));
    connect(ui->check_discount, SIGNAL(clicked(bool)), this, SLOT(EnableDiscount(bool)));
    connect(ui->check_model, SIGNAL(clicked(bool)), this, SLOT(EnableModel(bool)));
    connect(ui->check_qty, SIGNAL(clicked(bool)), this, SLOT(EnableQuantity(bool)));
    connect(ui->check_sell, SIGNAL(clicked(bool)), this, SLOT(EnableSellPrice(bool)));
    connect(ui->check_size, SIGNAL(clicked(bool)), this, SLOT(EnableSize(bool)));
    connect(ui->check_type, SIGNAL(clicked(bool)), this, SLOT(EnableType(bool)));

    ui->field_categorie->addWidget(category_box);
    ui->field_type->addWidget(type_box);
    ui->field_taille->addWidget(size_box);
    ui->field_couleur->addWidget(color_box);
}

recherche::~recherche()
{
    delete ui;
}

void recherche::InitValues()
{
    category_box->SetSelection(0);
    type_box->SetSelection(GetCategory(), 0);
    size_box->SetSelection(0);
    color_box->SetSelection(0);
    ui->achat_spin->setValue(0);
    ui->vente_spin->setValue(0);
    ui->model_spin->setValue(0);
    ui->rabais_spin->setValue(0);
    ui->qty_spin->setValue(0);
    ui->date_edit->setDate(QDate::currentDate());
    ui->refca->setValue(0);
    ui->reft->setValue(0);
    ui->refm->setValue(0);
    ui->refs->setValue(0);
    ui->refco->setValue(0);

    ui->equ_buy->setCurrentIndex(EQUAL);
    ui->equ_delivery->setCurrentIndex(EQUAL);
    ui->equ_discount->setCurrentIndex(EQUAL);
    ui->equ_qty->setCurrentIndex(EQUAL);
    ui->equ_sell->setCurrentIndex(EQUAL);
    ui->equ_size->setCurrentIndex(EQUAL);
}

void recherche::EnableCategory(bool e)
{
    category_box->setEnabled(e);
    ui->label_cat->setEnabled(e);
    ui->refca->setEnabled(e);
    ui->check_cat->setChecked(e);

    if(e == true)
        changedRefCat();
    else
        EnableType(false);
}

void recherche::EnableType(bool e)
{
    type_box->setEnabled(e);
    ui->label_type->setEnabled(e);
    ui->reft->setEnabled(e);
    ui->check_type->setChecked(e);


    if (e == true)
    {
        EnableCategory(true);
        changedRefType();
        reloadCategoryBox();
    }
    else
    {
        EnableModel(false);
    }
}

void recherche::EnableModel(bool e)
{
    ui->model_spin->setEnabled(e);
    ui->label_model->setEnabled(e);
    ui->refm->setEnabled(e);
    ui->check_model->setChecked(e);

    if (e == true)
    {
        EnableType(true);
        changedRefModele();
    }
}

void recherche::EnableSize(bool e)
{
    size_box->setEnabled(e);
    ui->equ_size->setEnabled(e);
    ui->refs->setEnabled(e);
    ui->check_size->setChecked(e);

    if (e == true)
        changedRefSize();
}

void recherche::EnableColor(bool e)
{
    color_box->setEnabled(e);
    ui->label_color->setEnabled(e);
    ui->refco->setEnabled(e);
    ui->check_color->setChecked(e);

    if (e == true)
        changedRefColor();
}

void recherche::EnableQuantity(bool e)
{
    ui->qty_spin->setEnabled(e);
    ui->equ_qty->setEnabled(e);
    ui->check_qty->setChecked(e);
}

void recherche::EnableBuyPrice(bool e)
{
    ui->achat_spin->setEnabled(e);
    ui->equ_buy->setEnabled(e);
    ui->check_buy->setChecked(e);
}

void recherche::EnableSellPrice(bool e)
{
    ui->vente_spin->setEnabled(e);
    ui->equ_sell->setEnabled(e);
    ui->check_sell->setChecked(e);
}

void recherche::EnableDiscount(bool e)
{
    ui->rabais_spin->setEnabled(e);
    ui->equ_discount->setEnabled(e);
    ui->check_discount->setChecked(e);
}

void recherche::EnableDelivery(bool e)
{
    ui->date_edit->setEnabled(e);
    ui->equ_delivery->setEnabled(e);
    ui->check_delivery->setChecked(e);
}

void recherche::Reinitialiser()
{
    // sélection et valeurs
    InitValues();

    // enable (false)
    EnableBuyPrice(false);
    EnableCategory(false);
    EnableColor(false);
    EnableDelivery(false);
    EnableDiscount(false);
    EnableModel(false);
    EnableQuantity(false);
    EnableSellPrice(false);
    EnableSize(false);
    EnableType(false);

    reinit = true;
}

int recherche::GetRefCategory()
{
    return ui->refca->value();
}

int recherche::GetCategory()
{
    return category_box->currentIndex();
}

int recherche::GetRefType()
{
    return ui->reft->value();
}

int recherche::GetType()
{
    return type_box->currentIndex();
}

int recherche::GetRefModel()
{
    return ui->refm->value();
}

int recherche::GetModel()
{
    return ui->model_spin->value();
}

int recherche::GetRefSize()
{
    return ui->refs->value();
}

int recherche::GetSize()
{
    return size_box->GetIndex(size_box->currentIndex());
}

int recherche::GetRefColor()
{
    return ui->refco->value();
}

int recherche::GetColor()
{
    return color_box->currentIndex();
}

int recherche::GetQuantity()
{
    return ui->qty_spin->value();
}

float recherche::GetBuyPrice()
{
    return ui->achat_spin->value();
}

float recherche::GetSellPrice()
{
    return ui->vente_spin->value();
}

int recherche::GetDiscount()
{
    return ui->rabais_spin->value();
}

QDate recherche::GetDelivery()
{
    return ui->date_edit->date();
}

void recherche::on_annuler_clicked()
{
    vect.Clear();
    this->close();
}

void recherche::on_valider_clicked()
{
    int ca = NR;
    int ty = NR;
    int mo = NR;
    int si = NR;
    int co = NR;
    int qt = NR;
    int di = NR;
    float bp = NR;
    float sp = NR;
    QDate da = QDate();
    EQ equ_size = ui->equ_size->currentIndex();
    EQ equ_qty = ui->equ_qty->currentIndex();
    EQ equ_buy = ui->equ_buy->currentIndex();
    EQ equ_sell = ui->equ_sell->currentIndex();
    EQ equ_disc = ui->equ_discount->currentIndex();
    EQ equ_del = ui->equ_delivery->currentIndex();

    if (ui->check_cat->isChecked())
        ca = GetRefCategory();
    if (ui->check_type->isChecked())
        ty = GetRefType();
    if (ui->check_model->isChecked())
        mo = GetRefModel();
    if (ui->check_size->isChecked())
        si = GetRefSize();
    if (ui->check_color->isChecked())
        co = GetRefColor();
    if (ui->check_qty->isChecked())
        qt = GetQuantity();
    if (ui->check_buy->isChecked())
        bp = GetBuyPrice();
    if (ui->check_sell->isChecked())
        sp = GetSellPrice();
    if (ui->check_discount->isChecked())
        di = GetDiscount();
    if (ui->check_delivery->isChecked())
        da = GetDelivery();

    if (ca == NR &&
        ty == NR &&
        mo == NR &&
        si == NR &&
        co == NR &&
        qt == NR &&
        di == NR &&
        bp == NR &&
        sp == NR &&
        da.isNull())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Recherche", "Vous devez donner au moins un critère de recherche en cochant une case.");
    }
    else
    {
        StockArticle sa((Ref){ca,ty,mo,si,co},NR,bp,sp,di,da);
        vect = stock->GetArticles(sa, equ_size, equ_qty,equ_buy,equ_sell,equ_disc,equ_del);

        if (Empty())
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Recherche", "Aucun résultat !");
        }
        else
        {
            reinit = false;
            this->close();
        }
    }
}

void recherche::reloadCategoryBox()
{
    delete type_box;
    type_box = new ComboBoxType(this, GetCategory(), GetRefType());
    ui->field_type->addWidget(type_box);
    connect(type_box, SIGNAL(currentIndexChanged(int)), this, SLOT(changedType()));
}

void recherche::changedCat()
{
    ui->refca->setValue(GetCategory());

    if (ui->check_type->isChecked())
        reloadCategoryBox();
}

void recherche::changedType()
{
    ui->reft->setValue(GetType());
}

void recherche::changedSize()
{
    ui->refs->setValue(GetSize());
}

void recherche::changedColor()
{
    ui->refco->setValue(GetColor());
}

void recherche::changedModele()
{
    ui->refm->setValue(GetModel());
}

void recherche::changedRefCat()
{
    category_box->SetSelection(GetRefCategory());
}

void recherche::changedRefType()
{
    type_box->SetSelection(GetRefCategory(),GetRefType());
}

void recherche::changedRefSize()
{
    size_box->SetSelection(GetRefSize());
}

void recherche::changedRefColor()
{
    color_box->SetSelection(GetRefColor());
}

void recherche::changedRefModele()
{
    ui->model_spin->setValue(GetRefModel());
}

void recherche::on_reinit_clicked()
{
    Reinitialiser();
    vect.Clear();
}

bool recherche::Empty()
{
    return vect.Empty();
}

bool recherche::ReInit()
{
    return reinit;
}
