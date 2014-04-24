#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>

#include "comboboxcolor.h"
#include "comboboxcategory.h"
#include "comboboxtype.h"
#include "comboboxsize.h"
#include "enregistrement.h"
#include "stock.h"
#include "ajoutstock.h"

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
    void DeleteStock();
    void FillTableRO();
    void FillTableRW();
    void InsertRowRO(int r, StockArticle* sa);
    void InsertRowRW(int r, StockArticle* sa);
    
private slots:
    void on_stock_add_clicked();

private:
    Ui::MainWindow *ui;
    Stock* stock;
};

#endif // MAINWINDOW_H
