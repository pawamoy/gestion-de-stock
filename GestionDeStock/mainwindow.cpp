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

    // connexion raccourci CTRL-S aux fonctions de sauvegarde
    QShortcut *scCtrlS = new QShortcut(QKeySequence("Ctrl+S"), this);
    connect(scCtrlS, SIGNAL(activated()), this, SLOT(on_ctrl_s()));

    // stock et ventes non modifiées de base
    stockmodified = false;
    sellsmodified = false;

    // chemins fichiers stock et vente initialisés aux valeurs par défaut
    stockfile = QString(DEFAULT_STOCK);
    sellsfile = QString(DEFAULT_SELLS);

    // coloration du 3ème onglet en noir
    ui->tabWidget->tabBar()->setTabTextColor(2,QColor("Black"));

    // lecture stock et remplissage table
    OpenStock(stockfile);
    FillStockTable();

    // lecture ventes et remplissage table
    OpenSells(sellsfile);
    FillSellsTable();

    // affichage de l'état
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
    StockModified(false);
    if (!s.isNull())
        stock->ReadStockFile(s);
}

void MainWindow::OpenSells(QString s)
{
    sells = new Sells();
    SellsModified(false);
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

void MainWindow::FillSellsTable()
{
    int i,s = sells->GetSellsSize();

    ui->tableWidget_2->setRowCount(0);
    for (i=0; i<s; i++)
        InsertSellsRow(i, sells->GetArticleN(i));
}

void MainWindow::InsertStockRow(int r, StockArticle* sa)
{
    ui->tableWidget->insertRow(r);
    SetStockRow(r, sa);
}

void MainWindow::InsertSellsRow(int r, SoldArticle* sa)
{
    ui->tableWidget_2->insertRow(r);
    SetSellsRow(r, sa);
}

void MainWindow::DeleteStockRow(int r)
{
    ui->tableWidget->removeRow(r);
}

void MainWindow::DeleteSellsRow(int r)
{
    ui->tableWidget_2->removeRow(r);
}

void MainWindow::SetStockRow(int r, StockArticle* sa)
{
    SetTableRow(ui->tableWidget, r, sa);
}

// valeurs modifiables
/*
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
*/

void MainWindow::SetSellsRow(int r, SoldArticle* sa)
{
    SetTableRow(ui->tableWidget_2, r, sa);

    QLabel* date_s = new QLabel(sa->GetSellDateString(DEFAULT_DATE_SEP));
    date_s->setAlignment((Qt::AlignHCenter | Qt::AlignVCenter));
    ui->tableWidget_2->setCellWidget(r,11,date_s);
}

void MainWindow::SetTableRow(QTableWidget* table, int row, Article* a)
{
    // déclaration des labels
    QLabel* ref = new QLabel(a->GetReferenceString());
    ref->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* categ = new QLabel(a->GetCategoryName());
    categ->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* type = new QLabel(a->GetTypeName());
    type->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* model = new QLabel(a->GetModelString());
    model->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* color = new QLabel(a->GetColorName());
    color->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* size = new QLabel(a->GetSizeName());
    size->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* qty = new QLabel(a->GetQuantityString());
    qty->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* achat = new QLabel(a->GetBuyPriceString());
    achat->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel* vente = new QLabel(a->GetSellPriceString());
    vente->setAlignment((Qt::AlignHCenter | Qt::AlignVCenter));
    QLabel* rabais = new QLabel(a->GetDiscountPercentString());
    rabais->setAlignment((Qt::AlignHCenter | Qt::AlignVCenter));
    QLabel* date_l = new QLabel(a->GetDeliveryString(DEFAULT_DATE_SEP));
    date_l->setAlignment((Qt::AlignHCenter | Qt::AlignVCenter));

    // affectation aux cellules de la ligne r
    table->setCellWidget(row,0,ref);
    table->setCellWidget(row,1,categ);
    table->setCellWidget(row,2,type);
    table->setCellWidget(row,3,model);
    table->setCellWidget(row,4,size);
    table->setCellWidget(row,5,color);
    table->setCellWidget(row,6,qty);
    table->setCellWidget(row,7,achat);
    table->setCellWidget(row,8,vente);
    table->setCellWidget(row,9,rabais);
    table->setCellWidget(row,10,date_l);
}

void MainWindow::StockModified(bool m)
{
    stockmodified = m;
    if (m == true)
        ui->tabWidget->tabBar()->setTabTextColor(0,QColor("Red"));
    else
        ui->tabWidget->tabBar()->setTabTextColor(0,QColor("Black"));
}

void MainWindow::SellsModified(bool m)
{
    sellsmodified = m;
    if (m == true)
        ui->tabWidget->tabBar()->setTabTextColor(1,QColor("Red"));
    else
        ui->tabWidget->tabBar()->setTabTextColor(1,QColor("Black"));
}

/** ************ SLOTS ************* **/

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
        StockModified(true);
    }

    FillStockTable();
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
        StockModified(true);
    }
}

void MainWindow::on_stock_mod_clicked()
{
    int col = ui->tableWidget->currentColumn();
    int row = ui->tableWidget->currentRow();

    if(col != -1 && row != -1)
    {
        StockArticle* articleCourant = stock->GetArticleN(row);
        StockArticle old_article = *articleCourant;
        modifStock* w = new modifStock(this, stock, articleCourant);

        w->exec();

        if ( !articleCourant->EquivalentTo(old_article) )
        {
            QString state = QString("Etat: modification de l'article ");
            ui->etat->setText(state.append(articleCourant->GetReferenceString()));
            SetStockRow(row, articleCourant);
            StockModified(true);
        }
    }
}

void MainWindow::on_actionEnregistrer_Stock_triggered()
{
    if (!stockfile.isNull())
    {
        stock->WriteStockFile(stockfile);
        QString state = QString("Etat: stock enregistré dans le fichier ");
        ui->etat->setText(state.append(stockfile));
        StockModified(false);
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
        SellsModified(false);
    }
    else
    {
        on_actionEnregistrer_Vente_sous_triggered();
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch (index)
    {
    case 0:
        ui->etat->setText("Etat: consultation du stock ");
        break;

    case 1:
        ui->etat->setText("Etat: consultation des ventes ");
        break;

    case 2:
        ui->etat->setText("Etat: consultation des informations");
        ui->nb_model->setText(QString::number(stock->GetStockSize()));
        ui->nb_article->setText(stock->GetTotalArticle());
    default:
        break;
    }
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
    StockModified(false);
}

void MainWindow::on_actionNouvelle_Vente_triggered()
{
    ClearSellsTable();
    DeleteSells();
    sellsfile = QString();
    OpenSells();
    ui->etat->setText("Etat: nouvelle table de ventes ouverte");
    SellsModified(false);
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

        ui->tabWidget->setCurrentIndex(0);
        stockfile = fileName;
        OpenStock(fileName);
        FillStockTable();
        StockModified(false);
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

        ui->tabWidget->setCurrentIndex(1);
        sellsfile = fileName;
        OpenSells(fileName);
        FillSellsTable();
        SellsModified(false);
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
        StockModified(false);
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
        SellsModified(false);
    }
}

void MainWindow::on_ctrl_s()
{
    switch (ui->tabWidget->currentIndex())
    {
    case 0:
        on_actionEnregistrer_Stock_triggered();
        break;

    case 1:
        on_actionEnregistrer_Vente_triggered();
        break;

    default:
        break;
    }
}

void MainWindow::on_sells_add_clicked()
{
    ajoutVente* w = new ajoutVente(this, stock, sells);
    ui->etat->setText("Etat: déclaration d'une nouvelle vente");
    w->exec();

//    size = stock->GetStockSize();
//    if (old_size < size)
//    {
//        StockArticle* sa = stock->GetArticleN(size-1);
//        InsertStockRow(size-1, sa);
//        QString state = QString("Etat: ajouté l'article ");
//        ui->etat->setText(state.append(sa->GetReferenceString()));
//        StockModified(true);
//    }
}

void MainWindow::on_stock_sell_clicked()
{
    int row = ui->tableWidget->currentRow();
    StockArticle* articleCourant = stock->GetArticleN(row);

    vente* w = new vente(this, stock, sells, articleCourant);
    ui->etat->setText("Etat: vente en cours");
    w->exec();

    FillStockTable();
    FillSellsTable();
}

void MainWindow::on_actionEnregistrement_triggered()
{
    on_stock_add_clicked();
}

void MainWindow::on_actionVente_triggered()
{
    on_sells_add_clicked();
}

void MainWindow::on_actionA_Propos_triggered()
{
    QMessageBox::about(this, QString("A propos"), QString("Interface graphique et logiciel conçus dans le cadre d'un projet de licence d'Informatique à Strasbourg. Concepteurs: Mohammed Yassine Jazouani, Timothée Mazzucotelli"));
}

void MainWindow::on_actionA_Propos_de_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_lancer_requete1_clicked()
{
    // chiffre d'affaire sur livraison jour précis
    SoldArticle* sa;
    QDate selected_date = ui->date_requete1->date();
    int i, s = sells->GetSellsSize();
    float recette = 0.0;

    ui->date_result1->setText(selected_date.toString());

    for (i=0; i<s; i++)
    {
        sa = sells->GetArticleN(i);
        if (sa->Delivered(selected_date))
            recette += sa->GetDiscountPrice();
    }

    ui->recette_result1->setText(QString::number(recette));
}

void MainWindow::on_lancer_requete2_clicked()
{
    // chiffre d'affaire depuis jour précis
    SoldArticle* sa;
    QDate selected_date = ui->date_requete1->date();
    int i, s = sells->GetSellsSize();
    float recette = 0.0;

    ui->date_result1->setText(selected_date.toString());

    for (i=0; i<s; i++)
    {
        sa = sells->GetArticleN(i);
        if (sa->DeliveredLately(selected_date))
            recette += sa->GetDiscountPrice();
    }

    ui->recette_result1->setText(QString::number(recette));
}
