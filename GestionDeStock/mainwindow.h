#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>
#include <QFileDialog>
#include <QTableWidget>
#include <QShortcut>
#include <QMessageBox>
#include <QCloseEvent>

#include "comboboxcolor.h"
#include "comboboxcategory.h"
#include "comboboxtype.h"
#include "comboboxsize.h"
#include "stock.h"
#include "sells.h"
#include "ajoutstock.h"
#include "modifstock.h"
#include "ajoutvente.h"
#include "vente.h"
#include "recherche.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ClearStockTable();
    void ClearSellsTable();
    void OpenStock(QString s=QString());
    void OpenSells(QString s=QString());
    void DeleteStock();
    void DeleteSells();
    void FillStockTable();
    void FillSellsTable();
    void InsertStockRow(int r, StockArticle* sa);
    void InsertSellsRow(int r, SoldArticle* sa);
    void SetStockRow(int r, StockArticle* sa);
    void SetSellsRow(int r, SoldArticle* sa);
    //void SetRowRW(int r, StockArticle* sa);
    void SetTableRow(QTableWidget* table, int row, Article* a);
    void DeleteStockRow(int r);
    void DeleteSellsRow(int r);
    void StockModified(bool m);
    void SellsModified(bool m);
    int Quitter();
    
private slots:
    void on_stock_add_clicked();
    void on_stock_del_clicked();
    void on_stock_mod_clicked();
    void on_actionEnregistrer_Stock_triggered();
    void on_actionEnregistrer_Vente_triggered();
    void on_tabWidget_currentChanged(int index);
    void on_actionQuitter_triggered();
    void on_actionNouveau_Stock_triggered();
    void on_actionNouvelle_Vente_triggered();
    void on_actionOuvrir_Stock_triggered();
    void on_actionOuvrir_Vente_triggered();
    void on_actionEnregistrer_Stock_sous_triggered();
    void on_actionEnregistrer_Vente_sous_triggered();
    void on_ctrl_s();
    void on_sells_add_clicked();
    void on_sells_cancel_clicked();
    void on_actionEnregistrement_triggered();
    void on_actionVente_triggered();
    void on_actionA_Propos_triggered();
    void on_actionA_Propos_de_Qt_triggered();
    void on_stock_sell_clicked();
    void on_lancer_requete1_clicked();
    void on_lancer_requete2_clicked();
    void on_tabulation();
    void on_stock_search_clicked();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    recherche* search;
    Stock* stock;
    Sells* sells;
    QString stockfile;
    QString sellsfile;
    bool stockmodified;
    bool sellsmodified;
};

#endif // MAINWINDOW_H
