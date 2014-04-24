#include "ajoutstock.h"
#include "ui_ajoutstock.h"

ajoutStock::ajoutStock(QWidget *parent, Stock *st) :
    QDialog(parent),
    ui(new Ui::ajoutStock)
{
    ui->setupUi(this);

    stock = st;

    //connect(ui->annuler, SIGNAL(clicked()), this, SLOT(on_annuler_clicked()));
    //connect(ui->valider, SIGNAL(clicked()), this, SLOT(on_valider_clicked()));

    ComboBoxCategory* c = new ComboBoxCategory(this);
    ComboBoxType* t = new ComboBoxType(this, 0);
    ComboBoxSize* s = new ComboBoxSize(this);
    ComboBoxColor* o = new ComboBoxColor(this);

    ui->field_categorie->addWidget(c);
    ui->field_type->addWidget(t);
    ui->field_taille->addWidget(s);
    ui->field_couleur->addWidget(o);
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
    this->close();
}
