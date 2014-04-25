#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DEFAULT_STOCK "../appdata/stock"
#define MAX_QUANTITY 9999
#define DEFAULT_DATE_SEP "/"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    OpenStock(DEFAULT_STOCK);
    FillTableRO();
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
    sells = new Stock();
    if (s != NULL)
        stock->ReadStockFile(s);
}

void MainWindow::DeleteStock()
{
    if (stock != NULL)
        delete stock;
}

void MainWindow::FillTableRO()
{
    int i,s = stock->GetStockSize();

    ui->tableWidget->setRowCount(0);
    for (i=0; i<s; i++)
        InsertRowRO(i, stock->GetArticleN(i));
}

void MainWindow::FillTableRW()
{
    int i,s = stock->GetStockSize();

    ui->tableWidget->setRowCount(0);
    for (i=0; i<s; i++)
        InsertRowRW(i, stock->GetArticleN(i));
}

// lecture seule
void MainWindow::InsertRowRO(int r, StockArticle* sa)
{
    ui->tableWidget->insertRow(r);
    SetRowRO(r, sa);
}

// valeurs modifiables
void MainWindow::InsertRowRW(int r, StockArticle* sa)
{
    ui->tableWidget->insertRow(r);
    SetRowRW(r, sa);
}

// lecture seule
void MainWindow::SetRowRO(int r, StockArticle* sa)
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
void MainWindow::SetRowRW(int r, StockArticle* sa)
{
    // déclaration des widgets
    ComboBoxCategory* categ = new ComboBoxCategory(ui->tableWidget, sa->GetCategoryInt());
    ComboBoxType* type = new ComboBoxType(ui->tableWidget, sa->GetCategoryInt(), sa->GetCategoryInt());
    QSpinBox* model = new QSpinBox(ui->tableWidget);
    model->setMaximum(9);
    model->setValue(sa->GetModelInt());
    ComboBoxSize* size = new ComboBoxSize(ui->tableWidget, sa->GetSizeInt());
    ComboBoxColor* color = new ComboBoxColor(ui->tableWidget, sa->GetColorInt());
    QSpinBox* qty = new QSpinBox(ui->tableWidget);
    qty->setMaximum(MAX_QUANTITY);
    qty->setValue(sa->GetQuantity());

    // affectation aux cellules de la ligne r
    ui->tableWidget->setItem(r,0,new QTableWidgetItem(sa->GetReferenceString()));
    ui->tableWidget->setCellWidget(r,1,categ);
    ui->tableWidget->setCellWidget(r,2,type);
    ui->tableWidget->setCellWidget(r,3,model);
    ui->tableWidget->setCellWidget(r,4,size);
    ui->tableWidget->setCellWidget(r,5,color);
    ui->tableWidget->setCellWidget(r,6,qty);
}

void MainWindow::on_stock_add_clicked()
{
    //Enregistrement *w = new Enregistrement(this);

    int size, old_size = stock->GetStockSize();

    ajoutStock* w = new ajoutStock(this, stock);
    w->exec();

    size = stock->GetStockSize();
    if (old_size < size)
        InsertRowRO(size-1, stock->GetArticleN(size-1));
}
