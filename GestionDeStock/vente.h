#ifndef VENTE_H
#define VENTE_H

#include <QDialog>

#include "stock.h"
#include "sells.h"

namespace Ui {
class vente;
}

class vente : public QDialog
{
    Q_OBJECT

public:
    explicit vente(QWidget *parent = 0,  Stock *st = NULL, Sells *se = NULL, StockArticle *ac = NULL);
    ~vente();

private slots:
    void on_valider_clicked();

    void on_annuler_clicked();

private:
    Ui::vente *ui;
    Stock* s;
    Sells* se;
    StockArticle* a;
};

#endif // VENTE_H
