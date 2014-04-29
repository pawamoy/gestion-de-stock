#include "sells.h"

/***** Opérations sur le vecteur *****/
/*************************************/
SeVector::SeVector()
{
    sells = new std::vector<SoldArticle*>();
}

SeVector::~SeVector()
{
    // est-ce que ça désalloue les Article ??? (attention)
    //delete sells;
}

SoldArticle* SeVector::Get(int i)
{
	try
	{
        return sells->at(i);
	}
	catch (const std::out_of_range& oor)
	{
		std::cerr << "Out of Range error: " << oor.what() << std::endl;
		return NULL;
	}
}

void SeVector::Add(SoldArticle* sa)
{
	sells->push_back(sa);
}

void SeVector::Del(int i)
{
	sells->erase(sells->begin()+i);
}

void SeVector::Clear()
{
	sells->clear();
}

int SeVector::Size()
{
	return sells->size();
}

bool SeVector::Empty()
{
	return (Size() == 0);
}


/**** Constructeurs, Destructeur *****/
/*************************************/
Sells::Sells()
{
	sells = SeVector();
}

Sells::~Sells()
{
	sells.Clear();
    //delete &sells;
}

void Sells::ReadSellsFile(QString path)
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
    int ref, qty, discount, yeard, years, monthd, months, dayd, days;
	float buy, sell;
	// début boucle lecture
	while (fo >> ref)
	{
        fo >> qty >> buy >> sell >> discount;
        fo >> yeard >> monthd >> dayd;
        fo >> years >> months >> days;
		
        New(ref, qty, buy, sell, discount, QDate(yeard, monthd, dayd), QDate(years, months, days));
	}
	
	fo.close();
}

void Sells::WriteSellsFile(QString path)
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
    int i, s = sells.Size();
    SoldArticle* sa;
    QDate date_l, date_s;
   // const char* ref; = ba.constData();
	// début boucle écriture
	for (i=0; i<s; i++)
	{
		sa = sells.Get(i);
        ba = sa->GetReferenceString().toUtf8();
        fs << ba.constData() << " ";
        fs << sa->GetQuantity() << " ";
		fs << sa->GetBuyPrice() << " ";
		fs << sa->GetSellPrice() << " ";
        fs << sa->GetDiscountPercent() << " ";
        date_l = sa->GetDeliveryDate();
        fs << date_l.year() << " ";
        fs << date_l.month() << " ";
        fs << date_l.day() << " ";
        date_s = sa->GetDeliveryDate();
        fs << date_s.year() << " ";
        fs << date_s.month() << " ";
        fs << date_s.day() << std::endl;
	}
	
	fs.close();
}

void Sells::Print(SoldArticle* sa)
{
    QByteArray ba = sa->GetReferenceString().toUtf8();
    QDate date = sa->GetDeliveryDate();
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Référence: " << ba.constData() << std::endl;
    //ba = sa->GetCategoryName().toUtf8();
    //std::cout << "Catégorie: " << ba.constData() << std::endl;
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

void Sells::PrintOne(int i)
{
    Print(sells.Get(i));
}

void Sells::PrintAll()
{
    int i, s = sells.Size();

    for(i=0; i<s; i++)
        PrintOne(i);
}

/************ Accesseurs *************/
/*************************************/
SoldArticle* Sells::GetArticleN(int i)
{
	return sells.Get(i);
}

int Sells::GetPosition(SoldArticle* sa)
{
	int i, s = sells.Size();
	
	for (i=0; i<s; i++)
	{
		if (sells.Get(i) == sa)
			return i;
	}
	
	return -1;
}

// first occurence
SoldArticle* Sells::GetArticle(int ref)
{
	int i, s = sells.Size();
	SoldArticle* a;
	
	for (i=0; i<s; i++)
	{
		a = sells.Get(i);
		if (a->HasReference(ref))
			return a;
	}
	
	return NULL;
}

SoldArticle* Sells::GetArticle(Ref ref)
{
	int i, s = sells.Size();
	SoldArticle* a;
	
	for (i=0; i<s; i++)
	{
		a = sells.Get(i);
		if (a->HasReference(ref))
			return a;
	}
	
	return NULL;
}

SoldArticle* Sells::GetArticle(SoldArticle sa)
{
	int i, s = sells.Size();
	SoldArticle* a;
	
	for (i=0; i<s; i++)
	{
		a = sells.Get(i);
		if (a->EquivalentTo(sa))
			return a;
	}
	
	return NULL;
}

// all occurences (remember to destroy result after treatment)
SeVector Sells::GetArticles(int ref)
{
	SeVector v = SeVector();
	
	int i, s = sells.Size();
	SoldArticle* a;
	
	for (i=0; i<s; i++)
	{
		a = sells.Get(i);
		if (a->HasReference(ref))
			v.Add(a);
	}
	
	return v;
}

SeVector Sells::GetArticles(Ref ref)
{
	SeVector v = SeVector();
	
	int i, s = sells.Size();
	SoldArticle* a;
	
	for (i=0; i<s; i++)
	{
		a = sells.Get(i);
		if (a->HasReference(ref))
			v.Add(a);
	}
	
	return v;
}

SeVector Sells::GetArticles(SoldArticle sa)
{
	SeVector v = SeVector();
	
	int i, s = sells.Size();
	SoldArticle* a;
	
	for (i=0; i<s; i++)
	{
		a = sells.Get(i);
		if (a->EquivalentTo(sa))
			v.Add(a);
	}
	
	return v;
}

int Sells::GetSellsSize()
{
    return sells.Size();
}

int Sells::GetTotalArticle()
{
    int i, s = GetSellsSize();
    int total = 0;

    for (i=0; i<s; i++)
        total += GetArticleN(i)->GetQuantity();

    return total;
}

// attention, penser à stocker les infos de sa avant d'appeler cette fonction
StockArticle Sells::ToStock(SoldArticle* sa)
{
    StockArticle a = StockArticle(
                sa->GetReferenceRef(),
                NR,
                sa->GetBuyPrice(),
                sa->GetSellPrice(),
                sa->GetDiscountPercent(),
                sa->GetDeliveryDate());

    sells.Del(GetPosition(sa));
    return a;
}


/********** Modificateurs ************/
/*************************************/
void Sells::ClearSells()
{
	sells.Clear();
}

// error if all infos are not provided
void Sells::New(SoldArticle* sa)
{
    if (sa->IsValid() && sa->HasValidSellDate())
        sells.Add(sa);
	else
		std::cerr << "SoldArticle sa is NOT valid" << std::endl;
}

void Sells::New(int r, int q, float bp, float sp, int di, QDate de, QDate se)
{
    StockArticle tempsa = StockArticle(r,q,bp,sp,di,de);

    if (tempsa.IsValid() && !se.isNull())
    {
        SoldArticle* na = new SoldArticle(tempsa, q, se);
        sells.Add(na);
    }
    else
    {
        std::cerr << "SoldArticle sa is NOT valid" << std::endl;
    }
}

void Sells::New(Ref r, int q, float bp, float sp, int di, QDate de, QDate se)
{
    StockArticle tempsa = StockArticle(r,q,bp,sp,di,de);

    if (tempsa.IsValid() && !se.isNull())
    {
        SoldArticle* na = new SoldArticle(tempsa, q, se);
        sells.Add(na);
    }
    else
    {
        std::cerr << "SoldArticle sa is NOT valid" << std::endl;
    }
}


/************* Testeurs **************/
/*************************************/
bool Sells::Contains(int reference)
{
	if (GetArticle(reference) != NULL)
		return true;
	else
		return false;
}

bool Sells::Contains(Ref reference)
{
	if (GetArticle(reference) != NULL)
		return true;
	else
		return false;
}

bool Sells::Contains(SoldArticle sa)
{
	if (GetArticle(sa) != NULL)
		return true;
	else
		return false;
}

bool Sells::Contains(SoldArticle* sa)
{
	if (GetPosition(sa) != -1)
		return true;
	else
		return false;
}

