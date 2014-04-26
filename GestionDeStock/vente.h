#ifndef VENTE_H
#define VENTE_H

#include <QDialog>

#include "stock.h"

namespace Ui {
class vente;
}

class vente : public QDialog
{
    Q_OBJECT

public:
    explicit vente(QWidget *parent = 0, StockArticle *ac = NULL);
    ~vente();

private:
    Ui::vente *ui;
};

#endif // VENTE_H
