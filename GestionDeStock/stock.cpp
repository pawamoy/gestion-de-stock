#include "stock.h"

/***** Opérations sur le vecteur *****/
/*************************************/
StVector::StVector()
{
    stock = new std::vector<StockArticle*>();
}

StVector::~StVector()
{
    // est-ce que ça désalloue les Article ??? (attention)
    //delete stock;
}

StockArticle* StVector::Get(int i)
{
	try
	{
        return stock->at(i);
	}
	catch (const std::out_of_range& oor)
	{
		std::cerr << "Out of Range error: " << oor.what() << std::endl;
		return NULL;
	}
}

void StVector::Add(StockArticle* sa)
{
	stock->push_back(sa);
}

void StVector::Del(int i)
{
	stock->erase(stock->begin()+i);
}

void StVector::Clear()
{
	stock->clear();
}

int StVector::Size()
{
	return stock->size();
}

bool StVector::Empty()
{
	return (Size() == 0);
}


/**** Constructeurs, Destructeur *****/
/*************************************/
Stock::Stock()
{
	stock = StVector();
}

Stock::~Stock()
{
	stock.Clear();
    //delete &stock;
}

void Stock::ReadStockFile(QString path)
{
	// if a QString is provided
    QByteArray ba = path.toUtf8();
    const char* cpath = ba.constData();
	
    std::ifstream fo(cpath, std::ios::in);
	
	if (!fo) {
        std::cerr << "Unable to open " << cpath << " in read-mode" << std::endl;
		return;
	}

	// déclaration des variables
	int ref, qty, discount, year, month, day;
	float buy, sell;
	// début boucle lecture
	while (fo >> ref)
	{
        fo >> qty >> buy >> sell >> discount;
		fo >> year >> month >> day;
		
        New(ref, qty, buy, sell, discount, QDate(year, month, day));
	}
	
	fo.close();
}

void Stock::WriteStockFile(QString path)
{
	// if a QString is provided
    QByteArray ba = path.toUtf8();
    const char* cpath = ba.constData();
	
    std::ofstream fs(cpath, std::ios::out);
	
	if (!fs) {
        std::cerr << "Unable to open " << cpath << " in write-mode" << std::endl;
		return ;
	}

	// déclaration des variables
    int i, s = stock.Size();
    StockArticle* sa;
    QDate date;
   // const char* ref; = ba.constData();
	// début boucle écriture
	for (i=0; i<s; i++)
	{
		sa = stock.Get(i);
        ba = sa->GetReferenceString().toUtf8();
        fs << ba.constData() << " ";
		fs << sa->GetQuantity() << " ";
		fs << sa->GetBuyPrice() << " ";
		fs << sa->GetSellPrice() << " ";
        fs << sa->GetDiscountPercent() << " ";
        date = sa->GetDeliveryDate();
        fs << date.year() << " ";
        fs << date.month() << " ";
        fs << date.day() << std::endl;
	}
	
	fs.close();
}

void Stock::Print(StockArticle* sa)
{
    QByteArray ba = sa->GetReferenceString().toUtf8();
    QDate date = sa->GetDeliveryDate();
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Référence: " << ba.constData() << std::endl;
    ba = sa->GetCategoryName().toUtf8();
    std::cout << "Catégorie: " << ba.constData() << std::endl;
    ba = sa->GetTypeName().toUtf8();
    std::cout << "Type     : " << ba.constData() << std::endl;
    //ba = sa->GetModelName().toUtf8();
    //std::cout << "Modèle   : " << ba.constData() << std::endl;
    std::cout << "Modèle n°: " << sa->GetModelInt() << std::endl;
    ba = sa->GetSizeName().toUtf8();
    std::cout << "Taille   : " << ba.constData() << std::endl;
    ba = sa->GetColorName().toUtf8();
    std::cout << "Couleur  : " << ba.constData() << std::endl;
    std::cout << "Quantité : " << sa->GetQuantity() << std::endl;
    std::cout << "Achat    : " << sa->GetBuyPrice() << std::endl;
    std::cout << "Vente    : " << sa->GetSellPrice() << std::endl;
    std::cout << "Rabais   : " << sa->GetDiscountPercent() << std::endl;
    std::cout << "Livraison: " << date.year() << "/" << date.month() << "/" << date.day() << std::endl;
}

void Stock::PrintOne(int i)
{
    Print(stock.Get(i));
}

void Stock::PrintAll()
{
    int i, s = stock.Size();

    for(i=0; i<s; i++)
        PrintOne(i);
}

/************ Accesseurs *************/
/*************************************/
StockArticle* Stock::GetArticleN(int i)
{
	return stock.Get(i);
}

int Stock::GetPosition(StockArticle* sa)
{
	int i, s = stock.Size();
	
	for (i=0; i<s; i++)
	{
		if (stock.Get(i) == sa)
			return i;
	}
	
	return -1;
}

// first occurence
StockArticle* Stock::GetArticle(int ref)
{
	int i, s = stock.Size();
	StockArticle* a;
	
	for (i=0; i<s; i++)
	{
		a = stock.Get(i);
		if (a->HasReference(ref))
			return a;
	}
	
	return NULL;
}

StockArticle* Stock::GetArticle(Ref ref)
{
	int i, s = stock.Size();
	StockArticle* a;
	
	for (i=0; i<s; i++)
	{
		a = stock.Get(i);
		if (a->HasReference(ref))
			return a;
	}
	
	return NULL;
}

StockArticle* Stock::GetArticle(StockArticle sa)
{
	int i, s = stock.Size();
	StockArticle* a;
	
	for (i=0; i<s; i++)
	{
		a = stock.Get(i);
		if (a->EquivalentTo(sa))
			return a;
	}
	
	return NULL;
}

// all occurences (remember to destroy result after treatment)
StVector Stock::GetArticles(int ref)
{
	StVector v = StVector();
	
	int i, s = stock.Size();
	StockArticle* a;
	
	for (i=0; i<s; i++)
	{
		a = stock.Get(i);
		if (a->HasReference(ref))
			v.Add(a);
	}
	
	return v;
}

StVector Stock::GetArticles(Ref ref)
{
	StVector v = StVector();
	
	int i, s = stock.Size();
	StockArticle* a;
	
	for (i=0; i<s; i++)
	{
		a = stock.Get(i);
		if (a->HasReference(ref))
			v.Add(a);
	}
	
	return v;
}

StVector Stock::GetArticles(StockArticle sa)
{
	StVector v = StVector();
	
	int i, s = stock.Size();
	StockArticle* a;
	
	for (i=0; i<s; i++)
	{
		a = stock.Get(i);
		if (a->EquivalentTo(sa))
			v.Add(a);
	}
	
	return v;
}

int Stock::GetStockSize()
{
    return stock.Size();
}

int Stock::GetTotalArticle()
{
    int i, s = GetStockSize();
    int total = 0;

    for (i=0; i<s; i++)
        total += GetArticleN(i)->GetQuantity();

    return total;
}

SoldArticle* Stock::ToSell(StockArticle* sa, int qty, QDate d)
{
	if (qty > 0)
	{
		// on crée le nouvel article vendu à partir l'article en stock
        SoldArticle* ns = new SoldArticle(*sa, qty, d);
		
		// on retire le nombre d'articles vendus du stock
        sa->SubQty(qty);
		
		// s'il n'y a plus d'articles, on supprime la référence
        // on fera ce traitement au niveau supérieur, pour enlever la ligne du tableau si besoin
        if (sa->GetQuantity() == 0)
            stock.Del(GetPosition(sa));
			
		// on renvoie la nouvelle vente
		return ns;
	}
	else
	{
		return NULL;
	}
}


/********** Modificateurs ************/
/*************************************/
void Stock::ClearStock()
{
	stock.Clear();
}

// error if all infos are not provided
void Stock::New(StockArticle sa)
{
	if (sa.IsValid())
	{
		StockArticle* na = new StockArticle(
			sa.GetReferenceRef(),
			sa.GetQuantity(),
			sa.GetBuyPrice(),
			sa.GetSellPrice(),
			sa.GetDiscountPercent(),
            sa.GetDeliveryDate());
			
		stock.Add(na);
	}
	else
	{
		std::cerr << "StockArticle sa is NOT valid" << std::endl;
	}
}

void Stock::New(StockArticle* sa)
{
	if (sa->IsValid())
        stock.Add(sa);
	else
		std::cerr << "StockArticle sa is NOT valid" << std::endl;
}

void Stock::New(int r, int q, float bp, float sp, int di, QDate de)
{
	StockArticle* na = new StockArticle(r, q, bp, sp, di, de);
	
	if (na->IsValid())
	{
		stock.Add(na);
	}
	else
	{
		std::cerr << "StockArticle sa is NOT valid" << std::endl;
		delete na;;
	}
}

void Stock::New(Ref r, int q, float bp, float sp, int di, QDate de)
{
	StockArticle* na = new StockArticle(r, q, bp, sp, di, de);
	
	if (na->IsValid())
	{
		stock.Add(na);
	}
	else
	{
		std::cerr << "StockArticle sa is NOT valid" << std::endl;
		delete na;;
	}
}

void Stock::Add(int ref, int qty) //! all occurences
{
	StVector v = GetArticles(ref);
	Add(v, qty);
    //delete &v;
}

void Stock::Add(Ref ref, int qty) //! all occurences
{
	StVector v = GetArticles(ref);
	Add(v, qty);
    //delete &v;
}

void Stock::Add(StockArticle* sa, int qty) // exact occurence
{
	sa->AddQty(qty);
}

void Stock::Add(StVector sv, int qty) // exact occurences
{
	int i, s = sv.Size();
	
	if (s > 0)
		for (i=0; i<s; i++)
			sv.Get(i)->AddQty(qty);
}

void Stock::Remove(int ref, int qty) //! all occurences
{
	StVector v = GetArticles(ref);
	Remove(v, qty);
    //delete &v;
}

void Stock::Remove(Ref ref, int qty) //! all occurences
{
	StVector v = GetArticles(ref);
	Remove(v, qty);
    //delete &v;
}

void Stock::Remove(StockArticle* sa, int qty) // exact occurence
{
	sa->SubQty(qty);
}

void Stock::Remove(StVector sv, int qty) // exact occurences
{
	int i, s = sv.Size();
	
	if (s > 0)
		for (i=0; i<s; i++)
			sv.Get(i)->SubQty(qty);
}

// no error, modify what is provided
void Stock::Modify(int refa, StockArticle sb) //! all occurences
{
	StVector v = GetArticles(refa);
	Modify(v, sb);
    //delete &v;
}

void Stock::Modify(Ref refa, StockArticle sb) //! all occurences
{
	StVector v = GetArticles(refa);
	Modify(v, sb);
    //delete &v;
}

void Stock::Modify(StockArticle* sa, StockArticle sb) // exact occurence
{
	if (sb.HasValidReference())
		sa->SetReference(sb.GetReferenceRef());
	else
	{
		if (sb.HasValidCategory())
			sa->SetCategory(sb.GetCategoryInt());
		
		if (sb.HasValidType())
			sa->SetType(sb.GetTypeInt());
		
		if (sb.HasValidModel())
			sa->SetModel(sb.GetModelInt());
		
		if (sb.HasValidSize())
			sa->SetSize(sb.GetSizeInt());
		
		if (sb.HasValidColor())
			sa->SetColor(sb.GetColorInt());
	}
	
	if (sb.HasValidQuantity())
		sa->SetQuantity(sb.GetQuantity());
	
	if (sb.HasValidBuyPrice())
		sa->SetBuyPrice(sb.GetBuyPrice());
	
	if (sb.HasValidSellPrice())
		sa->SetSellPrice(sb.GetSellPrice());
	
	if (sb.HasValidDiscount())
        sa->SetDiscountPercent(sb.GetDiscountPercent());
	
	if (sb.HasValidDelivery())
		sa->SetDeliveryDate(sb.GetDeliveryDate());
}

void Stock::Modify(StVector sv, StockArticle sb) // exact occurences
{
	int i, s = sv.Size();
	
	if (s > 0)
	{
		if (sb.HasValidReference())
		{
			Ref tr = sb.GetReferenceRef();
			for (i=0; i<s; i++)
				sv.Get(i)->SetReference(tr);
		}
		else
		{
			if (sb.HasValidCategory())
			{
				int c = sb.GetCategoryInt();
				for (i=0; i<s; i++)
					sv.Get(i)->SetCategory(c);
			}
			
			if (sb.HasValidType())
			{
				int t = sb.GetTypeInt();
				for (i=0; i<s; i++)
					sv.Get(i)->SetType(t);
			}
			
			if (sb.HasValidModel())
			{
				int m = sb.GetModelInt();
				for (i=0; i<s; i++)
					sv.Get(i)->SetModel(m);
			}
			
			if (sb.HasValidSize())
			{
				int z = sb.GetSizeInt();
				for (i=0; i<s; i++)
					sv.Get(i)->SetSize(z);
			}
			
			if (sb.HasValidColor())
			{
				int o = sb.GetColorInt();
				for (i=0; i<s; i++)
					sv.Get(i)->SetColor(o);
			}
		}
		
		if (sb.HasValidQuantity())
		{
			int q = sb.GetQuantity();
			for (i=0; i<s; i++)
				sv.Get(i)->SetQuantity(q);
		}
		
		if (sb.HasValidBuyPrice())
		{
			float p = sb.GetBuyPrice();
			for (i=0; i<s; i++)
				sv.Get(i)->SetBuyPrice(p);
		}
		
		if (sb.HasValidSellPrice())
		{
			float p = sb.GetSellPrice();
			for (i=0; i<s; i++)
				sv.Get(i)->SetSellPrice(p);
		}
		
		if (sb.HasValidDiscount())
		{
			int d = sb.GetDiscountPercent();
			for (i=0; i<s; i++)
                sv.Get(i)->SetDiscountPercent(d);
		}
		
		if (sb.HasValidDelivery())
		{
			QDate d = sb.GetDeliveryDate();
			for (i=0; i<s; i++)
				sv.Get(i)->SetDeliveryDate(d);
		}
	}
}

// error if all sb's infos are not provided
void Stock::Replace(int refa, StockArticle sb) //! all occurences
{
	if (sb.IsValid())
	{
		StVector v = GetArticles(refa);
		Replace(v, sb);
        //delete &v;
	}
	else
	{
		std::cerr << "StockArticle sb is NOT valid" << std::endl;
	}
}

void Stock::Replace(Ref refa, StockArticle sb) //! all occurences
{
	if (sb.IsValid())
	{
		StVector v = GetArticles(refa);
		Replace(v, sb);
        //delete &v;
	}
	else
	{
		std::cerr << "StockArticle sb is NOT valid" << std::endl;
	}
}

void Stock::Replace(StockArticle* sa, StockArticle sb) // exact occurence
{
	if (sb.IsValid())
		sa->Replace(sb);
	else
		std::cerr << "StockArticle sb is NOT valid" << std::endl;
}

void Stock::Replace(StVector sv, StockArticle sb) // exact occurences
{
	if (sb.IsValid())
	{
		int i, s = sv.Size();
		
		if (s > 0)
			for (i=0; i<s; i++)
				sv.Get(i)->Replace(sb);
	}
	else
	{
		std::cerr << "StockArticle sb is NOT valid" << std::endl;
	}
}

void Stock::Del(int i)
{
    stock.Del(i);
}


/************* Testeurs **************/
/*************************************/
bool Stock::Contains(int reference)
{
	if (GetArticle(reference) != NULL)
		return true;
	else
		return false;
}

bool Stock::Contains(Ref reference)
{
	if (GetArticle(reference) != NULL)
		return true;
	else
		return false;
}

bool Stock::Contains(StockArticle sa)
{
	if (GetArticle(sa) != NULL)
		return true;
	else
		return false;
}

bool Stock::Contains(StockArticle* sa)
{
	if (GetPosition(sa) != -1)
		return true;
	else
		return false;
}

