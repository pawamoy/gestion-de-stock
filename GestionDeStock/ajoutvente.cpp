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

    UpdateFinalPrice(0);
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
    int ca = GetRefCategory();
    int ty = GetRefType();
    int mo = GetRefModel();
    int si = GetRefSize();
    int co = GetRefColor();
    int qt = GetQuantity();
    float bp = GetBuyPrice();
    float sp = GetSellPrice();
    int di = GetDiscount();
    QDate de = GetDelivery();
    QDate sd = GetSellDate();

    Ref ref = {ca,ty,mo,si,co};
    StockArticle a(ref, NR, bp, sp, di, de);
    StockArticle *na = stock->GetArticle(a);

    if (na != NULL)
    {
        SoldArticle* nsa = stock->ToSell(na, qt, sd);
        if (nsa != NULL)
        {
            sells->New(nsa);
            this->close();
        }
        else
        {
            QString msg = QString("Quantité trop importante (maximum ");
            msg = msg.append(QString::number(na->GetQuantity()));
            msg = msg.append(QString(") !"));
            QMessageBox messageBox;
            messageBox.critical(0,"Erreur", msg);
        }
    }
    else
    {
        QString msg = QString("Aucun article correspondant dans le stock !");
        QMessageBox messageBox;
        messageBox.critical(0,"Erreur", msg);
    }
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

void ajoutVente::on_vente_spin_valueChanged()
{
    UpdateFinalPrice();
}

void ajoutVente::on_rabais_spin_valueChanged()
{
    UpdateFinalPrice();
}

void ajoutVente::on_quantite_spin_valueChanged()
{
    UpdateFinalPrice();
}

void ajoutVente::UpdateFinalPrice(float montant)
{
    QString euros = QString(" euros");

    if (montant == -1)
    {
        montant = GetSellPrice();
        montant -= ((montant * GetDiscount()) / 100);
        montant *= GetQuantity();
    }

    ui->montant_final->setText(QString::number(montant).append(euros));
}
