#ifndef MODIFSTOCK_H
#define MODIFSTOCK_H

#include <QDialog>

#include "stock.h"
#include "comboboxcategory.h"
#include "comboboxcolor.h"
#include "comboboxsize.h"
#include "comboboxtype.h"

namespace Ui {
class modifStock;
}

class modifStock : public QDialog
{
    Q_OBJECT

public:
    explicit modifStock(QWidget *parent = 0, Stock* s = NULL, StockArticle* ac = NULL);
    ~modifStock();
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

private:
    Ui::modifStock *ui;
    Stock* stock;
    StockArticle* article;
    ComboBoxCategory* category_box;
    ComboBoxType* type_box;
    ComboBoxSize* size_box;
    ComboBoxColor* color_box;

private slots:
    void on_annuler_clicked();
    void on_valider_clicked();
    void changeCat();
};

#endif // modifSTOCK_H
