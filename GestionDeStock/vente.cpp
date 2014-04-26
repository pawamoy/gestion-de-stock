#include "vente.h"
#include "ui_vente.h"

vente::vente(QWidget *parent,  Stock *st, Sells *se, StockArticle* ac) :
    QDialog(parent),
    ui(new Ui::vente)
{
    ui->setupUi(this);

    s = st;
    this->se = se;
    a = ac;

    QString state = QString("Vente de l'article ");
    state = state.append(ac->GetReferenceString());
    ui->label->setText(state);

    state = QString("Quantité vendue (maximum: ");
    state = state.append(ac->GetQuantityString());
    state = state.append(QString(")"));
    ui->label_2->setText(state);

    on_spinBox_valueChanged(1);

    ui->spinBox->setMaximum(ac->GetQuantity());
}

vente::~vente()
{
    delete ui;
}

void vente::on_valider_clicked()
{
    SoldArticle* sa = s->ToSell(a,ui->spinBox->value());

    if (sa != NULL)
    {
        se->New(sa);
    }
    else
    {
        QString msg = QString("Quantité trop importante (maximum ");
        msg = msg.append(QString::number(a->GetQuantity()));
        msg = msg.append(QString(") !"));
        QMessageBox messageBox;
        messageBox.critical(0,"Erreur", msg);
    }

    this->close();
}

void vente::on_annuler_clicked()
{
    this->close();
}

void vente::on_spinBox_valueChanged(int arg1)
{

    float montantTotal = (a->GetDiscountPrice())*arg1;

    QString text ("Montant total de la vente : ");
    QString text2 (" €");
    text.append(QString::number(montantTotal));
    text.append(text2);
    ui->label_3->setText(text);
}
