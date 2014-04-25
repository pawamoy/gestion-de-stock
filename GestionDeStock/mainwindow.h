#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>

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

    void OpenStock(const char* s);
    void OpenSells(const char* s);
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
    void DeleteStockRow(int r);
    void DeleteSellsRow(int r);
    
private slots:
    void on_stock_add_clicked();

    void on_stock_del_clicked();

    void on_stock_mod_clicked();

private:
    Ui::MainWindow *ui;
    Stock* stock;
    Sells* sells;
};

#endif // MAINWINDOW_H
