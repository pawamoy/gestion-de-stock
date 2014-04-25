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

    category_box = new ComboBoxCategory(this, 0);
    type_box = new ComboBoxType(this, 0, 0);
    size_box = new ComboBoxSize(this, 0);
    color_box = new ComboBoxColor(this, 0);

    ui->field_categorie->addWidget(category_box);
    ui->field_type->addWidget(type_box);
    ui->field_taille->addWidget(size_box);
    ui->field_couleur->addWidget(color_box);
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
