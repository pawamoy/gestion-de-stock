#ifndef AJOUTVENTE_H
#define AJOUTVENTE_H

#include <QDialog>
#include <QMessageBox>

#include "stock.h"
#include "sells.h"

namespace Ui {
class ajoutVente;
}

class ajoutVente : public QDialog
{
    Q_OBJECT
    
public:
    explicit ajoutVente(QWidget *parent = 0, Stock *st=NULL, Sells *se=NULL);
    ~ajoutVente();
    int GetRefCategory();
    int GetRefType();
    int GetRefModel();
    int GetRefSize();
    int GetRefColor();
    int GetQuantity();
    float GetBuyPrice();
    float GetSellPrice();
    int GetDiscount();
    QDate GetDelivery();
    QDate GetSellDate();
    void UpdateFinalPrice(float montant=-1);
    
private:
    Ui::ajoutVente *ui;
    Stock* stock;
    Sells* sells;

private slots:
    void on_annuler_clicked();
    void on_valider_clicked();
    void on_vente_spin_valueChanged();
    void on_rabais_spin_valueChanged();
    void on_quantite_spin_valueChanged();
};

#endif // AJOUTVENTE_H
