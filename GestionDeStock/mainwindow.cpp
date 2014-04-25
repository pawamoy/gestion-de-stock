#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DEFAULT_APPDATA "../appdata"
#define DEFAULT_STOCK "../appdata/stock.s"
#define DEFAULT_SELLS "../appdata/sells.v"
#define SAVE_AS_STOCK "../appdata/untitled.s"
#define SAVE_AS_SELLS "../appdata/untitled.v"
#define MAX_QUANTITY 9999
#define DEFAULT_DATE_SEP "/"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stockfile = QString(DEFAULT_STOCK);
    sellsfile = QString(DEFAULT_SELLS);

    OpenStock(stockfile);
    FillStockTable();

    OpenSells(sellsfile);
    FillSellsTable();

    ui->etat->setText("Etat: consultation du stock");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ClearStockTable()
{
    while (ui->tableWidget->rowCount() > 0)
        ui->tableWidget->removeRow(0);
}

void MainWindow::ClearSellsTable()
{
    while (ui->tableWidget_2->rowCount() > 0)
        ui->tableWidget_2->removeRow(0);
}

void MainWindow::OpenStock(QString s)
{
    stock = new Stock();
    if (!s.isNull())
        stock->ReadStockFile(s);
}

void MainWindow::OpenSells(QString s)
{
    sells = new Sells();
    if (!s.isNull())
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
    ui->etat->setText("Etat: ajout d'un article au stock");
    w->exec();

    size = stock->GetStockSize();
    if (old_size < size)
    {
        StockArticle* sa = stock->GetArticleN(size-1);
        InsertStockRow(size-1, sa);
        QString state = QString("Etat: ajouté l'article ");
        ui->etat->setText(state.append(sa->GetReferenceString()));
    }
}

void MainWindow::on_stock_del_clicked()
{
    int col = ui->tableWidget->currentColumn();
    int row = ui->tableWidget->currentRow();

    if(col != -1 && row != -1)
    {
        StockArticle* sa = stock->GetArticleN(row);
        DeleteStockRow(row);
        stock->Del(row);

        QString state = QString("Etat: supprimé l'article ");
        ui->etat->setText(state.append(sa->GetReferenceString()));
    }
}

void MainWindow::on_stock_mod_clicked()
{
    int col = ui->tableWidget->currentColumn();
    int row = ui->tableWidget->currentRow();

    if(col != -1 && row != -1)
    {
        StockArticle* articleCourant = stock->GetArticleN(row);
        modifStock* w = new modifStock(this, stock, articleCourant);

        QString state = QString("Etat: modification de l'article ");
        ui->etat->setText(state.append(articleCourant->GetReferenceString()));

        w->exec();

        SetStockRow(row, articleCourant);
    }
}

void MainWindow::on_actionEnregistrer_Stock_triggered()
{
    if (!stockfile.isNull())
    {
        stock->WriteStockFile(stockfile);
        QString state = QString("Etat: stock enregistré dans le fichier ");
        ui->etat->setText(state.append(stockfile));
    }
    else
    {
        on_actionEnregistrer_Stock_sous_triggered();
    }
}

void MainWindow::on_actionEnregistrer_Vente_triggered()
{
    if (!sellsfile.isNull())
    {
        sells->WriteSellsFile(sellsfile);
        QString state = QString("Etat: ventes enregistrées dans le fichier ");
        ui->etat->setText(state.append(sellsfile));
    }
    else
    {
        on_actionEnregistrer_Vente_sous_triggered();
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0)
        ui->etat->setText("Etat: consultation du stock ");
    else
        ui->etat->setText("Etat: consultation des ventes ");
}

void MainWindow::on_actionQuitter_triggered()
{
    DeleteStock();
    DeleteSells();
    this->close();
}

void MainWindow::on_actionNouveau_Stock_triggered()
{
    ClearStockTable();
    DeleteStock();
    stockfile = QString();
    OpenStock();
    ui->etat->setText("Etat: nouveau stock ouvert");
}

void MainWindow::on_actionNouvelle_Vente_triggered()
{
    ClearSellsTable();
    DeleteSells();
    sellsfile = QString();
    OpenSells();
    ui->etat->setText("Etat: nouvelle table de ventes ouverte");
}

void MainWindow::on_actionOuvrir_Stock_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier Stock"),
                                                     DEFAULT_APPDATA,
                                                     tr("Fichier Stock (*.s);;Tous les fichiers (*)"));
    if (!fileName.isNull())
    {
        QString state = QString("Etat: Ouverture du fichier ");
        ui->etat->setText(state.append(fileName));

        stockfile = fileName;
        OpenStock(fileName);
        FillStockTable();
    }
}

void MainWindow::on_actionOuvrir_Vente_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier Vente"),
                                                     DEFAULT_APPDATA,
                                                     tr("Fichier Vente (*.v);;Tous les fichiers (*)"));
    if (!fileName.isNull())
    {
        QString state = QString("Etat: Ouverture du fichier ");
        ui->etat->setText(state.append(fileName));

        sellsfile = fileName;
        OpenSells(fileName);
        FillSellsTable();
    }
}

void MainWindow::on_actionEnregistrer_Stock_sous_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Sauvegarder le stock"),
                                                    SAVE_AS_STOCK,
                                                    tr("Fichier Stock (*.s);;Tous les fichiers (*)"));
    if (!fileName.isNull())
    {
        QString state = QString("Etat: ventes enregistrées dans le fichier ");
        ui->etat->setText(state.append(fileName));

        stockfile = fileName;
        stock->WriteStockFile(fileName);
    }
}

void MainWindow::on_actionEnregistrer_Vente_sous_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Sauvegarder les ventes"),
                                                    SAVE_AS_SELLS,
                                                    tr("Fichier Vente (*.v);;Tous les fichiers (*)"));
    if (!fileName.isNull())
    {
        QString state = QString("Etat: stock enregistré dans le fichier ");
        ui->etat->setText(state.append(fileName));

        sellsfile = fileName;
        sells->WriteSellsFile(fileName);
    }
}
