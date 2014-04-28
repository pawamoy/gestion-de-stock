#ifndef RECHERCHE_H
#define RECHERCHE_H

#include <QDialog>
#include <QMessageBox>

#include "stock.h"
#include "comboboxcategory.h"
#include "comboboxcolor.h"
#include "comboboxsize.h"
#include "comboboxtype.h"

namespace Ui {
class recherche;
}

class recherche : public QDialog
{
    Q_OBJECT
    
public:
    explicit recherche(QWidget *parent = 0, Stock* st=NULL);
    ~recherche();
    void Reinitialiser();
    void InitValues();
    int GetRefCategory();
    int GetCategory();
    int GetRefType();
    int GetType();
    int GetRefModel();
    int GetModel();
    int GetRefSize();
    int GetSize();
    int GetRefColor();
    int GetColor();
    int GetQuantity();
    float GetBuyPrice();
    float GetSellPrice();
    int GetDiscount();
    QDate GetDelivery();
    void reloadCategoryBox();
    bool Empty();
    bool ReInit();

    StVector vect;
    
private:
    Ui::recherche *ui;
    Stock* stock;
    ComboBoxCategory* category_box;
    ComboBoxType* type_box;
    ComboBoxSize* size_box;
    ComboBoxColor* color_box;
    bool reinit;

private slots:
    void on_annuler_clicked();
    void on_valider_clicked();

    void changedCat();
    void changedType();
    void changedSize();
    void changedColor();
    void changedModele();

    void changedRefCat();
    void changedRefType();
    void changedRefSize();
    void changedRefColor();
    void changedRefModele();

    void EnableCategory(bool e);
    void EnableType(bool e);
    void EnableModel(bool e);
    void EnableSize(bool e);
    void EnableColor(bool e);
    void EnableQuantity(bool e);
    void EnableBuyPrice(bool e);
    void EnableSellPrice(bool e);
    void EnableDiscount(bool e);
    void EnableDelivery(bool e);

    void on_reinit_clicked();
};

#endif // RECHERCHE_H
