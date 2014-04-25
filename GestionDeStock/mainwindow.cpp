#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DEFAULT_STOCK "../appdata/stock"
#define DEFAULT_SELLS "../appdata/sells"
#define MAX_QUANTITY 9999
#define DEFAULT_DATE_SEP "/"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    OpenStock(DEFAULT_STOCK);
    FillStockTable();

    OpenSells(DEFAULT_SELLS);
    FillSellsTable();
    //ComboBoxCategory* test;
    //test = dynamic_cast<ComboBoxCategory*>(ui->tableWidget->cellWidget(1,1));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenStock(const char* s)
{
    stock = new Stock();
    if (s != NULL)
        stock->ReadStockFile(s);
}

void MainWindow::OpenSells(const char* s)
{
    sells = new Sells();
    if (s != NULL)
        sells->ReadSellsFile(s);
}

void MainWindow::DeleteStock()
{
    if (stock != NULL)
        delete stock;
}

void MainWindow::DeleteSells()
{
    if (sells != NULL)
        delete sells;
}

void MainWindow::FillStockTable()
{
    int i,s = stock->GetStockSize();

    ui->tableWidget->setRowCount(0);
    for (i=0; i<s; i++)
        InsertStockRow(i, stock->GetArticleN(i));
}

//void MainWindow::FillTableRW()
//{
//    int i,s = stock->GetStockSize();

//    ui->tableWidget->setRowCount(0);
//    for (i=0; i<s; i++)
//        InsertRowRW(i, stock->GetArticleN(i));
//}

void MainWindow::FillSellsTable()
{
    int i,s = sells->GetSellsSize();

    ui->tableWidget_2->setRowCount(0);
    for (i=0; i<s; i++)
        InsertSellsRow(i, sells->GetArticleN(i));
}

// lecture seule
void MainWindow::InsertStockRow(int r, StockArticle* sa)
{
    ui->tableWidget->insertRow(r);
    SetStockRow(r, sa);
}

// valeurs modifiables
//void MainWindow::InsertRowRW(int r, StockArticle* sa)
//{
//    ui->tableWidget->insertRow(r);
//    SetRowRW(r, sa);
//}

void MainWindow::InsertSellsRow(int r, SoldArticle* sa)
{
    ui->tableWidget_2->insertRow(r);
    SetSellsRow(r, sa);
}

void MainWindow::DeleteStockRow(int r)
{
    std::cout << "remove row " << r << std::endl;
    ui->tableWidget->removeRow(r);
}

void MainWindow::DeleteSellsRow(int r)
{
    std::cout << "remove row " << r << std::endl;
    ui->tableWidget_2->removeRow(r);
}

// lecture seule
void MainWindow::SetStockRow(int r, StockArticle* sa)
{
    // déclaration des widgets
    QLabel* ref = new QLabel(sa->GetReferenceString());
    ref->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* categ = new QLabel(sa->GetCategoryName());
    categ->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* type = new QLabel(sa->GetTypeName());
    type->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* model = new QLabel(sa->GetModelString());
    model->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* color = new QLabel(sa->GetColorName());
    color->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* size = new QLabel(sa->GetSizeName());
    size->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* qty = new QLabel(sa->GetQuantityString());
    qty->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* achat = new QLabel(sa->GetBuyPriceString());
    achat->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* vente = new QLabel(sa->GetSellPriceString());
    vente->setAlignment((Qt::AlignHCenter | Qt::AlignVCenter));
    QLabel* rabais = new QLabel(sa->GetDiscountPercentString());
    rabais->setAlignment((Qt::AlignHCenter | Qt::AlignVCenter));
    QLabel* date = new QLabel(sa->GetDeliveryString(DEFAULT_DATE_SEP));
    date->setAlignment((Qt::AlignHCenter | Qt::AlignVCenter));

    // affectation aux cellules de la ligne r
    ui->tableWidget->setCellWidget(r,0,ref);
    ui->tableWidget->setCellWidget(r,1,categ);
    ui->tableWidget->setCellWidget(r,2,type);
    ui->tableWidget->setCellWidget(r,3,model);
    ui->tableWidget->setCellWidget(r,4,size);
    ui->tableWidget->setCellWidget(r,5,color);
    ui->tableWidget->setCellWidget(r,6,qty);
    ui->tableWidget->setCellWidget(r,7,achat);
    ui->tableWidget->setCellWidget(r,8,vente);
    ui->tableWidget->setCellWidget(r,9,rabais);
    ui->tableWidget->setCellWidget(r,10,date);
}

// valeurs modifiables
//void MainWindow::SetRowRW(int r, StockArticle* sa)
//{
//    // déclaration des widgets
//    ComboBoxCategory* categ = new ComboBoxCategory(ui->tableWidget, sa->GetCategoryInt());
//    ComboBoxType* type = new ComboBoxType(ui->tableWidget, sa->GetCategoryInt(), sa->GetCategoryInt());
//    QSpinBox* model = new QSpinBox(ui->tableWidget);
//    model->setMaximum(9);
//    model->setValue(sa->GetModelInt());
//    ComboBoxSize* size = new ComboBoxSize(ui->tableWidget, sa->GetSizeInt());
//    ComboBoxColor* color = new ComboBoxColor(ui->tableWidget, sa->GetColorInt());
//    QSpinBox* qty = new QSpinBox(ui->tableWidget);
//    qty->setMaximum(MAX_QUANTITY);
//    qty->setValue(sa->GetQuantity());

//    // affectation aux cellules de la ligne r
//    ui->tableWidget->setItem(r,0,new QTableWidgetItem(sa->GetReferenceString()));
//    ui->tableWidget->setCellWidget(r,1,categ);
//    ui->tableWidget->setCellWidget(r,2,type);
//    ui->tableWidget->setCellWidget(r,3,model);
//    ui->tableWidget->setCellWidget(r,4,size);
//    ui->tableWidget->setCellWidget(r,5,color);
//    ui->tableWidget->setCellWidget(r,6,qty);
//}

void MainWindow::SetSellsRow(int r, SoldArticle* sa)
{
    // déclaration des widgets
    QLabel* ref = new QLabel(sa->GetReferenceString());
    ref->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* categ = new QLabel(sa->GetCategoryName());
    categ->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* type = new QLabel(sa->GetTypeName());
    type->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* model = new QLabel(sa->GetModelString());
    model->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* color = new QLabel(sa->GetColorName());
    color->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* size = new QLabel(sa->GetSizeName());
    size->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* qty = new QLabel(sa->GetQuantityString());
    qty->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* achat = new QLabel(sa->GetBuyPriceString());
    achat->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* vente = new QLabel(sa->GetSellPriceString());
    vente->setAlignment((Qt::AlignHCenter | Qt::AlignVCenter));
    QLabel* rabais = new QLabel(sa->GetDiscountPercentString());
    rabais->setAlignment((Qt::AlignHCenter | Qt::AlignVCenter));
    QLabel* date_l = new QLabel(sa->GetDeliveryString(DEFAULT_DATE_SEP));
    date_l->setAlignment((Qt::AlignHCenter | Qt::AlignVCenter));
    QLabel* date_s = new QLabel(sa->GetSellDateString(DEFAULT_DATE_SEP));
    date_s->setAlignment((Qt::AlignHCenter | Qt::AlignVCenter));

    // affectation aux cellules de la ligne r
    ui->tableWidget_2->setCellWidget(r,0,ref);
    ui->tableWidget_2->setCellWidget(r,1,categ);
    ui->tableWidget_2->setCellWidget(r,2,type);
    ui->tableWidget_2->setCellWidget(r,3,model);
    ui->tableWidget_2->setCellWidget(r,4,size);
    ui->tableWidget_2->setCellWidget(r,5,color);
    ui->tableWidget_2->setCellWidget(r,6,qty);
    ui->tableWidget_2->setCellWidget(r,7,achat);
    ui->tableWidget_2->setCellWidget(r,8,vente);
    ui->tableWidget_2->setCellWidget(r,9,rabais);
    ui->tableWidget_2->setCellWidget(r,10,date_l);
    ui->tableWidget_2->setCellWidget(r,11,date_s);
}

void MainWindow::on_stock_add_clicked()
{
    int size, old_size = stock->GetStockSize();

    ajoutStock* w = new ajoutStock(this, stock);
    w->exec();

    size = stock->GetStockSize();
    if (old_size < size)
        InsertStockRow(size-1, stock->GetArticleN(size-1));
}

void MainWindow::on_stock_del_clicked()
{
    if( ui->tableWidget->currentColumn() != -1 && ui->tableWidget->currentRow() != -1 )
    {
        std::cout << "ref : " << stock->GetArticleN(ui->tableWidget->currentRow())->GetReferenceString().toUtf8().constData() << std::endl;
        std::cout << "je suis ici" << std::endl;
        int tmp = ui->tableWidget->currentRow();
        stock->Remove(stock->GetArticleN(ui->tableWidget->currentRow()),ALL);
        DeleteStockRow(ui->tableWidget->currentRow());
        stock->Del(tmp);
    }
}

void MainWindow::on_stock_mod_clicked()
{
    if( ui->tableWidget->currentColumn() != -1 && ui->tableWidget->currentRow() != -1 )
    {
        StockArticle* articleCourant = stock->GetArticleN(ui->tableWidget->currentRow());
        modifStock* w = new modifStock(this, stock, articleCourant);
        w->exec();
    }
}
