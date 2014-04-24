#include "enregistrement.h"
#include "ui_enregistrement.h"
#include <iostream>

Enregistrement::Enregistrement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Enregistrement)
{
    ui->setupUi(this);

    ui->refmod->setValidator( new QIntValidator(1000, 9999, this) );
    ui->refcoul->setValidator( new QIntValidator(10, 99, this) );
    ui->reftaille->setValidator( new QIntValidator(10, 99, this) );

    ui->TXS->setChecked(true);

    ui->prixachat->setValidator( new QIntValidator(0, 999999999, this) );
    ui->prixvente->setValidator( new QIntValidator(0, 999999999, this) );
    ui->quantite->setValidator( new QIntValidator(0, 9999999999, this) );

    ui->listCategorie->setCurrentRow(0);
    ui->listType->setCurrentRow(0);

}

Enregistrement::~Enregistrement()
{
    delete ui;
}

void Enregistrement::on_Annuler_clicked()
{
    this->close();
}

int Enregistrement::getTaille()
{
    if( ui->TXS->isChecked() )
        return 0;
    if( ui->TS->isChecked() )
        return 1;
    if( ui->TM->isChecked() )
        return 2;
    if( ui->TL->isChecked() )
        return 3;
    if( ui->TXL->isChecked() )
        return 4;

    return -1;
}

int Enregistrement::getCouleur()
{
    std::string number = "";

    if( ui->CRouge->isChecked() )
        number = number + "1";
    if( ui->CVert->isChecked() )
        number = number + "2";
    if( ui->CBleu->isChecked() )
        number = number + "3";
    if( ui->CBlanc->isChecked() )
        number = number + "4";
    if( ui->CNoir->isChecked() )
        number = number + "5";

    return atoi(number.c_str());
}

int Enregistrement::getRefMod()
{
    if( atoi(ui->refmod->text().toUtf8().constData())/1000 < 1)
        return -1;

    else return atoi(ui->refmod->text().toUtf8().constData());

}

int Enregistrement::getRefCoul()
{
    if( atoi(ui->refcoul->text().toUtf8().constData())/10 < 1)
        return -1;

    else return atoi(ui->refcoul->text().toUtf8().constData());

}

int Enregistrement::getRefTaille()
{
    if( atoi(ui->reftaille->text().toUtf8().constData())/10 < 1)
        return -1;

    else return atoi(ui->reftaille->text().toUtf8().constData());

}

int Enregistrement::getDateDay()
{
    return ui->datelivraison->date().day();
}

int Enregistrement::getDateMonth()
{
    return ui->datelivraison->date().month();
}

int Enregistrement::getDateYear()
{
    return ui->datelivraison->date().year();
}

int Enregistrement::getPrixVente()
{
    return atoi(ui->prixvente->text().toUtf8().constData());
}

int Enregistrement::getPrixAchat()
{
    return atoi(ui->prixachat->text().toUtf8().constData());
}

int Enregistrement::getPourcentage()
{
    return atoi(ui->pourcentage->text().toUtf8().constData());
}

int Enregistrement::getQuantite()
{
    return atoi(ui->quantite->text().toUtf8().constData());
}

void Enregistrement::showSelectedItems()
{
    std::string s = ui->listCategorie->currentItem()->text().toUtf8().constData();
    std::cout << s << std::endl;
}


void Enregistrement::on_Valider_clicked()
{
    std::cout << "taille : " << getTaille() << std::endl;
    std::cout << "couleur : " << getCouleur() << std::endl;
    std::cout << "ref mod " << getRefMod() << std::endl;
    std::cout << "ref coul " << getRefCoul() << std::endl;
    std::cout << "ref taille " << getRefTaille() << std::endl;
    std::cout << "jour " << getDateDay() << std::endl;
    std::cout << "mois " << getDateMonth() << std::endl;
    std::cout << "annee " << getDateYear() << std::endl;
    std::cout << "prix achat " << getPrixAchat() << std::endl;
    std::cout << "prix vente " << getPrixVente() << std::endl;
    std::cout << "pourcentage " << getPourcentage() << std::endl;
    std::cout << "quantite " << getQuantite() << std::endl;
    showSelectedItems();

}
