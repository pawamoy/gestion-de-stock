#ifndef __ARTICLE_H
#define __ARTICLE_H

#include <QString>
#include <QDate>

#include "datasets.h"

#define NO_REF 99999999
#define NR -1
#define ALL NR

typedef struct str_ref
{
	int c, t, m, s, o;
} Ref;

class Article
{
	public:
        Article();
		
		int GetReferenceInt();
		Ref GetReferenceRef();
		QString GetReferenceString();
		int GetCategoryInt();
		QString GetCategoryString();
		int GetTypeInt();
		QString GetTypeString();
		int GetModelInt();
		QString GetModelString();
		int GetStock();
        QString GetStockString();
		float GetBuyPrice();
        QString GetBuyPriceString();
		float GetSellPrice();
		int GetDiscountPercent();
		float GetDiscountPrice();
		QDate GetDeliveryDate();
		int GetDaysInStock();
		int GetColorInt();
		QString GetColorString();
        RGB GetColorRGB();
		QString GetColorHexa();
		int GetSizeInt();
		QString GetSizeString();
		QString GetCategoryName();
		QString GetTypeName();
		QString GetSizeName();
		QString GetColorName();
		
		void ApplyDiscount(bool apply);
		
		bool HasReference(int r);
		bool HasReference(Ref r);
		//~ bool HasReference(QString r);
		bool HasCategory(int c);
		//~ bool HasCategory(QString c);
		bool HasType(int t);
		//~ bool HasType(QString t);
		bool HasModel(int m);
		//~ bool HasModel(QString m);
		bool HasSize(int s);
		//~ bool HasSize(QString s);
		bool HasColor(int c);
		//~ bool HasColor(QString c);
		bool HasQuantity(int q);
		bool HasMore(int q);
		bool HasLess(int q);
		bool Bought(float p);
		bool BoughtMore(float p);
		bool BoughtLess(float p);
		bool Costs(float p);
		bool CostsMore(float p);
		bool CostsLess(float p);
		bool HasDiscount(int d);
		bool HasDiscountMore(int d);
		bool HasDiscountLess(int d);
		bool Delivered(QDate d);
		bool DeliveredEarly(QDate d);
		bool DeliveredLately(QDate d);
		bool InStockFor(int days);
		bool SameAs(Article sa);
		bool HasSameCategory(Article sa);
		bool HasSameType(Article sa);
		bool HasSameModel(Article sa);
		bool HasSameSize(Article sa);
		bool HasSameColor(Article sa);
		float CompareBuyPrice(Article sa);
		float CompareSellPrice(Article sa);
		int CompareDiscount(Article sa);
		float CompareDiscountPrice(Article sa);
		int CompareStock(Article sa);
		int CompareDelivery(Article sa);
		bool EquivalentTo(Article a);
		bool IsValid();
		bool HasValidReference();
		bool HasValidCategory();
		bool HasValidType();
		bool HasValidModel();
		bool HasValidSize();
		bool HasValidColor();
		bool HasValidQuantity();
		bool HasValidBuyPrice();
		bool HasValidSellPrice();
		bool HasValidDiscount();
		bool HasValidDelivery();
		
    protected:
        int cat;
        int type;
        int model;
        int size;
        int color;
		int qty;
        float bprice;
        float sprice;
        int discount;
		QDate delivery;
};

class StockArticle: public Article
{
	public:
        StockArticle(int reference, int quantity, float buyprice, float sellprice, int discount_p, QDate delivery=QDate::currentDate());
        StockArticle(Ref reference, int quantity, float buyprice, float sellprice, int discount_p, QDate delivery=QDate::currentDate());
        //~ StockArticle(QString reference, int quantity, int buyprice, int sellprice, int discount_p, QDate delivery);
		
        void SetArticle(int reference, int quantity, float buyprice, float sellprice, int discount_p, QDate delivery=QDate::currentDate());
        void SetArticle(Ref reference, int quantity, float buyprice, float sellprice, int discount_p, QDate delivery=QDate::currentDate());
        //~ void SetArticle(QString reference, int quantity, float buyprice, float sellprice, int discount_p, QDate delivery);
        void SetQtyAndPrices(int q, float bp, float sp, int d);
		void SetReference(int r);
		void SetReference(Ref r);
		//~ void SetReference(QString r);
		void SetCategory(int c);
		void SetType(int t);
		void SetModel(int m);
		void SetSize(int s);
		void SetColor(int c);
		void SetQuantity(int q);
		void IncrementQty();
		void DecrementQty();
		void AddQty(int q);
		void SubQty(int q);
        void SetBuyPrice(float p);
        void SetSellPrice(float p);
		void SetDiscountPercent(int p);
		void SetDeliveryDate(QDate d);
		void Replace(StockArticle sa);
};

class SoldArticle: public Article
{
	public:
        SoldArticle(StockArticle sa, int quantity, QDate sell_date=QDate::currentDate());
		
		QDate GetSellDate();
		int GetDaysSinceSold();
		int GetDaysToSell();
		
		bool Sold(QDate d);
		bool SoldEarly(QDate d);
		bool SoldLately(QDate d);
		bool SoldSince(int days);
		bool SoldIn(int days);
		
		int CompareSellDay(SoldArticle sa);
		int CompareSellTime(SoldArticle sa);
		bool EquivalentTo(SoldArticle a);
		
	private:
		QDate selldate;
};

#endif // __ARTICLE_H
