#ifndef AJOUTSTOCK_H
#define AJOUTSTOCK_H

#include <QDialog>

#include "stock.h"
#include "comboboxcategory.h"
#include "comboboxcolor.h"
#include "comboboxsize.h"
#include "comboboxtype.h"

namespace Ui {
class ajoutStock;
}

class ajoutStock : public QDialog
{
    Q_OBJECT
    
public:
    explicit ajoutStock(QWidget *parent = 0, Stock* s = NULL);
    ~ajoutStock();
    
private:
    Ui::ajoutStock *ui;
    Stock* stock;

private slots:
    void on_annuler_clicked();
    void on_valider_clicked();
};

#endif // AJOUTSTOCK_H
