#ifndef AJOUTSTOCK_H
#define AJOUTSTOCK_H

#include <QDialog>

namespace Ui {
class ajoutStock;
}

class ajoutStock : public QDialog
{
    Q_OBJECT
    
public:
    explicit ajoutStock(QWidget *parent = 0);
    ~ajoutStock();
    
private:
    Ui::ajoutStock *ui;
};

#endif // AJOUTSTOCK_H
