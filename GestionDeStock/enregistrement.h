#ifndef ENREGISTREMENT_H
#define ENREGISTREMENT_H

#include <QDialog>

namespace Ui {
class Enregistrement;
}

class Enregistrement : public QDialog
{
    Q_OBJECT

public:
    explicit Enregistrement(QWidget *parent = 0);
    ~Enregistrement();

private slots:
    void on_Annuler_clicked();

    void on_Valider_clicked();

private:
    Ui::Enregistrement *ui;
    int getTaille();
    int getCouleur();
    int getRefMod();
    int getRefCoul();
    int getRefTaille();
    int getDateDay();
    int getDateMonth();
    int getDateYear();
    int getPrixVente();
    int getPrixAchat();
    int getPourcentage();
    int getQuantite();
    void showSelectedItems();
};

#endif // ENREGISTREMENT_H
