#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>
#include <QFileDialog>
#include <QTableWidget>
#include <QShortcut>

#include "comboboxcolor.h"
#include "comboboxcategory.h"
#include "comboboxtype.h"
#include "comboboxsize.h"
#include "stock.h"
#include "sells.h"
#include "ajoutstock.h"
#include "modifstock.h"

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
    //void FillTableRW();
    void InsertStockRow(int r, StockArticle* sa);
    void InsertSellsRow(int r, SoldArticle* sa);
    //void InsertRowRW(int r, StockArticle* sa);
    void SetStockRow(int r, StockArticle* sa);
    void SetSellsRow(int r, SoldArticle* sa);
    //void SetRowRW(int r, StockArticle* sa);
    void SetTableRow(QTableWidget* table, int row, Article* a);
    void DeleteStockRow(int r);
    void DeleteSellsRow(int r);
    void StockModified(bool m);
    void SellsModified(bool m);
    
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

private:
    Ui::MainWindow *ui;
    Stock* stock;
    Sells* sells;
    QString stockfile;
    QString sellsfile;
    bool stockmodified;
    bool sellsmodified;
};

#endif // MAINWINDOW_H
