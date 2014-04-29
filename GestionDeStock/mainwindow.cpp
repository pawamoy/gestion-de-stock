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

    // connexion raccourcis
    QShortcut *scCtrlS = new QShortcut(QKeySequence("Ctrl+S"), this);
    connect(scCtrlS, SIGNAL(activated()), this, SLOT(on_ctrl_s()));
    QShortcut *scDel = new QShortcut(QKeySequence("Del"), this);
    connect(scDel, SIGNAL(activated()), this, SLOT(on_stock_del_clicked()));
    QShortcut *scAdd = new QShortcut(QKeySequence("a"), this);
    connect(scAdd, SIGNAL(activated()), this, SLOT(on_stock_add_clicked()));
    QShortcut *scMod = new QShortcut(QKeySequence("m"), this);
    connect(scMod, SIGNAL(activated()), this, SLOT(on_stock_mod_clicked()));
    QShortcut *scVend = new QShortcut(QKeySequence("v"), this);
    connect(scVend, SIGNAL(activated()), this, SLOT(on_stock_sell_clicked()));
    QShortcut *scNewVente = new QShortcut(QKeySequence("n"), this);
    connect(scNewVente, SIGNAL(activated()), this, SLOT(on_sells_add_clicked()));
    QShortcut *scCancel = new QShortcut(QKeySequence("c"), this);
    connect(scCancel, SIGNAL(activated()), this, SLOT(on_sells_cancel_clicked()));
    QShortcut *scTab = new QShortcut(QKeySequence("Tab"), this);
    connect(scTab, SIGNAL(activated()), this, SLOT(on_tabulation()));

    // chemins fichiers stock et vente initialisés aux valeurs par défaut
    stockfile = QString(DEFAULT_STOCK);
    sellsfile = QString(DEFAULT_SELLS);

    // coloration du 3ème onglet en noir
    //ui->tabWidget->tabBar()->setTabTextColor(2,QColor("Black"));

    // lecture fichiers et remplissage tables
    OpenStock(stockfile);
    OpenSells(sellsfile);

    // instance fenetre recherche
    search = new recherche(this, stock);
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
    {
        stock->ReadStockFile(s);
        FillStockTable();
        ui->tableWidget->setCurrentCell(0,0);
    }
}

void MainWindow::OpenSells(QString s)
{
    sells = new Sells();
    SellsModified(false);
    if (!s.isNull())
    {
        sells->ReadSellsFile(s);
        FillSellsTable();
        ui->tableWidget_2->setCurrentCell(0,0);
    }
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
void MainWindow::SetSearchRow(QTableWidget* table, int row)
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
    int art, old_art = stock->GetTotalArticle();

    ajoutStock* w = new ajoutStock(this, stock);
    ui->etat->setText("ajout d'un article au stock");
    w->exec();

    size = stock->GetStockSize();
    art = stock->GetTotalArticle();
    if (old_size < size)
    {
        StockArticle* sa = stock->GetArticleN(size-1);
        InsertStockRow(size-1, sa);
        QString state = QString("ajouté l'article ");
        ui->etat->setText(state.append(sa->GetReferenceString()));
        StockModified(true);
    }
    else if (old_art < art)
    {
        ui->etat->setText("quantité ajoutée à un article existant");
        FillStockTable();
        StockModified(true);
    }
    else
    {
        ui->etat->setText("ajout annulé");
    }
}

void MainWindow::on_stock_del_clicked()
{
    if (ui->tabWidget->currentIndex() != 0)
        return;

    int row = ui->tableWidget->currentRow();

    if (row != -1)
    {
        StockArticle* sa = stock->GetArticleN(row);
        DeleteStockRow(row);
        stock->Del(row);

        QString state = QString("supprimé l'article ");
        ui->etat->setText(state.append(sa->GetReferenceString()));
        StockModified(true);
    }
}

void MainWindow::on_stock_mod_clicked()
{
    if (ui->tabWidget->currentIndex() != 0)
        return;

    int row = ui->tableWidget->currentRow();
    if (row != -1)
    {
        StockArticle* articleCourant = stock->GetArticleN(row);
        StockArticle old_article = *articleCourant;
        modifStock* w = new modifStock(this, stock, articleCourant);

        QString state = QString("modification de l'article ");
        ui->etat->setText(state.append(articleCourant->GetReferenceString()));

        w->exec();

        if ( !articleCourant->EquivalentTo(old_article) )
        {
            QString state = QString("modifié article ");
            ui->etat->setText(state.append(articleCourant->GetReferenceString()));
            SetStockRow(row, articleCourant);
            StockModified(true);
        }
        else
        {
            ui->etat->setText("modification annulée");
        }
    }
}

void MainWindow::on_actionEnregistrer_Stock_triggered()
{
    if (!stockfile.isNull())
    {
        stock->WriteStockFile(stockfile);
        QString state = QString("stock enregistré dans le fichier ");
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
        QString state = QString("ventes enregistrées dans le fichier ");
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
        //ui->etat->setText("consultation du stock ");
        break;

    case 1:
        //ui->etat->setText("consultation des ventes ");
        break;

    case 2:
        //ui->etat->setText("consultation des informations");
        ui->nb_model->setText(QString::number(stock->GetStockSize()).append(QString(" modèles")));
        ui->nb_article->setText(QString::number(stock->GetTotalArticle()).append(QString(" articles")));
    default:
        break;
    }
}

int MainWindow::Quitter()
{
    if (stockmodified == true)
    {
        QMessageBox msgBox;
        msgBox.setText("Le stock a été modifié.");
        msgBox.setInformativeText("Voulez-vous sauvegarder vos changements?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setButtonText(QMessageBox::Save, "Sauvegarder");
        msgBox.setButtonText(QMessageBox::Cancel, "Annuler");
        msgBox.setButtonText(QMessageBox::Discard, "Ne pas sauvegarder");
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Save:
              // Save was clicked
              on_actionEnregistrer_Stock_triggered();
              break;
          case QMessageBox::Discard:
              // Don't Save was clicked
              break;
          case QMessageBox::Cancel:
              // Cancel was clicked
              return 1;
          default:
              // should never be reached
              break;
        }
    }

    if (sellsmodified == true)
    {
        QMessageBox msgBox;
        msgBox.setText("Les ventes ont été modifiées.");
        msgBox.setInformativeText("Voulez-vous sauvegarder vos changements?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setButtonText(QMessageBox::Save, "Sauvegarder");
        msgBox.setButtonText(QMessageBox::Cancel, "Annuler");
        msgBox.setButtonText(QMessageBox::Discard, "Ne pas sauvegarder");
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Save:
              // Save was clicked
              on_actionEnregistrer_Vente_triggered();
              break;
          case QMessageBox::Discard:
              // Don't Save was clicked
              break;
          case QMessageBox::Cancel:
              // Cancel was clicked
              return 1;
          default:
              // should never be reached
              break;
        }
    }
    return 0;
}

void MainWindow::on_actionQuitter_triggered()
{
    if (Quitter() == 0)
    {
        DeleteStock();
        DeleteSells();
        this->close();
    }
}

void MainWindow::on_actionNouveau_Stock_triggered()
{
    ClearStockTable();
    DeleteStock();
    stockfile = QString();
    OpenStock();
    ui->etat->setText("nouveau stock ouvert");
    StockModified(false);
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_actionNouvelle_Vente_triggered()
{
    ClearSellsTable();
    DeleteSells();
    sellsfile = QString();
    OpenSells();
    ui->etat->setText("nouvelle table de ventes ouverte");
    SellsModified(false);
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_actionOuvrir_Stock_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier Stock"),
                                                     DEFAULT_APPDATA,
                                                     tr("Fichier Stock (*.s);;Tous les fichiers (*)"));
    if (!fileName.isNull())
    {
        QString state = QString("Ouverture du fichier ");
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
        QString state = QString("Ouverture du fichier ");
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
        QString state = QString("ventes enregistrées dans le fichier ");
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
        QString state = QString("stock enregistré dans le fichier ");
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
    int size, old_size = sells->GetSellsSize();
    SoldArticle* sa;

    ajoutVente* w = new ajoutVente(this, stock, sells);
    ui->etat->setText("déclaration d'une nouvelle vente");
    w->exec();

    size = sells->GetSellsSize();
    if (old_size < size)
    {
        sa = sells->GetArticleN(size-1);
        InsertSellsRow(size-1, sa);
        FillStockTable();
        QString state = QString("ajouté une vente du produit ");
        ui->etat->setText(state.append(sa->GetReferenceString()));
        SellsModified(true);
        StockModified(true);
    }
    else
    {
        ui->etat->setText("nouvelle vente annulée");
    }
}

void MainWindow::on_sells_cancel_clicked()
{
    if (ui->tabWidget->currentIndex() != 1)
        return;

    int row = ui->tableWidget_2->currentRow();

    if (row != -1)
    {
        SoldArticle* sa = sells->GetArticleN(row);
        QString ref = sa->GetReferenceString();
        int q = sa->GetQuantity();
        StockArticle a = sells->ToStock(sa);
        StockArticle* na = stock->GetArticle(a);

        if (na != NULL)
        {
            na->AddQty(q);
        }
        else
        {
            a.SetQuantity(q);
            stock->New(a);
        }

        QString state = QString("annulé la vente ");
        ui->etat->setText(state.append(ref));

        FillStockTable();
        DeleteSellsRow(row);
        StockModified(true);
        SellsModified(true);
    }
}

void MainWindow::on_stock_sell_clicked()
{
    if (ui->tabWidget->currentIndex() != 0)
            return;

    int row = ui->tableWidget->currentRow();
    if (row != -1)
    {
        int size, old_size = sells->GetTotalArticle();
        StockArticle* articleCourant = stock->GetArticleN(row);

        vente* w = new vente(this, stock, sells, articleCourant);
        QString state = QString("vente de l'article ");
        ui->etat->setText(state.append(articleCourant->GetReferenceString()));
        w->exec();

        size = sells->GetTotalArticle();
        if (old_size < size)
        {
            QString state = QString("vendu l'article ");
            ui->etat->setText(state.append(articleCourant->GetReferenceString()));
            FillStockTable();
            FillSellsTable();
            StockModified(true);
            SellsModified(true);
        }
        else
        {
            ui->etat->setText("vente annulée");
        }
    }
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
    float tmp;

    ui->date_result1->setText(selected_date.toString());

    for (i=0; i<s; i++)
    {
        sa = sells->GetArticleN(i);
        if (sa->Delivered(selected_date))
        {
            tmp = sa->GetDiscountPrice() - sa->GetBuyPrice();
            recette += tmp * sa->GetQuantity();
        }
    }

    ui->recette_result1->setText(QString::number(recette).append(QString(" euros")));
}

void MainWindow::on_lancer_requete2_clicked()
{
    // chiffre d'affaire depuis jour précis
    SoldArticle* sa;
    QDate selected_date = ui->date_requete2->date();
    int i, s = sells->GetSellsSize();
    float recette = 0.0;
    float tmp;

    ui->date_result2->setText(selected_date.toString());

    for (i=0; i<s; i++)
    {
        sa = sells->GetArticleN(i);
        if (sa->DeliveredLately(selected_date))
        {
            tmp = sa->GetDiscountPrice() - sa->GetBuyPrice();
            recette += tmp * sa->GetQuantity();
        }
    }

    ui->recette_result2->setText(QString::number(recette).append(QString(" euros")));
}

void MainWindow::on_tabulation()
{
    ui->tabWidget->setCurrentIndex((ui->tabWidget->currentIndex()+1)%3);
}

void MainWindow::on_stock_search_clicked()
{
    ui->etat->setText("application d'un filtre sur les articles (recherche)");
    search->exec();

    if (search->Empty())
    {
        if (search->ReInit())
            ui->etat->setText("filtre désactivé");
        else
            ui->etat->setText("recherche annulée");
    }
    else
    {
        QString state = QString("recherche finie avec succès: ");
        state = state.append(QString::number(search->vect.Size()));
        state = state.append(QString(" articles trouvés "));
        state = state.append("(Rechercher->Réinitialiser->Annuler pour afficher tous les produits)");
        ui->etat->setText(state);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (Quitter() == 1)
        event->ignore();
    else
        event->accept();
}
