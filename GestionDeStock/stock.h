#ifndef __STOCK_H
#define __STOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <QByteArray>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "article.h"

class StVector
{
	public:
		StVector();
		~StVector();
		StockArticle* Get(int i);
		void Add(StockArticle* sa);
		void Del(int i);
		void Clear();
		int Size();
		
		bool Empty();
	
	private:
		std::vector<StockArticle*>* stock;
};

class Stock
{
	public:
		Stock();
		~Stock();
		
		void ReadStockFile(const char* path);
		void WriteStockFile(const char* path);
        void Print(StockArticle* sa);
        void PrintOne(int i);
        void PrintAll();
		
		StockArticle* GetArticleN(int i);
		int GetPosition(StockArticle* sa);
		// first occurence
		StockArticle* GetArticle(int ref);
		StockArticle* GetArticle(Ref ref);
		StockArticle* GetArticle(StockArticle sa);
		// all occurences (remember to destroy result after treatment)
		StVector GetArticles(int ref);
		StVector GetArticles(Ref ref);
		StVector GetArticles(StockArticle sa);
        int GetStockSize();
		SoldArticle* GetSellFrom(StockArticle* sa, int qty, QDate d=QDate::currentDate());
		
		void ClearStock();
		// error if all infos are not provided
		void New(StockArticle sa);
		void New(StockArticle* sa);
		void New(int r, int q, float bp, float sp, int di, QDate de=QDate::currentDate());
		void New(Ref r, int q, float bp, float sp, int di, QDate de=QDate::currentDate());
		void Add(int ref, int qty); //! all occurences
		void Add(Ref ref, int qty); //! all occurences
		void Add(StockArticle* sa, int qty); // exact occurence
		void Add(StVector sv, int qty); // exact occurences
		void Remove(int ref, int qty); //! all occurences
		void Remove(Ref ref, int qty); //! all occurences
		void Remove(StockArticle* sa, int qty); // exact occurence
		void Remove(StVector sv, int qty); // exact occurences
		// no error, modify what is provided
		void Modify(int refa, StockArticle sb); //! all occurences
		void Modify(Ref refa, StockArticle sb); //! all occurences
		void Modify(StockArticle* sa, StockArticle sb); // exact occurence
		void Modify(StVector sv, StockArticle sb); // exact occurences
		// error if all sb's infos are not provided
		void Replace(int refa, StockArticle sb); //! all occurences
		void Replace(Ref refa, StockArticle sb); //! all occurences
		void Replace(StockArticle* sa, StockArticle sb); // exact occurence
		void Replace(StVector sv, StockArticle sb); // exact occurences
        void Del(int i);
		
		bool Contains(int reference);
		bool Contains(Ref reference);
		bool Contains(StockArticle sa);
		bool Contains(StockArticle* sa);
		
	private:
		StVector stock;
		
		// vector operations
		StVector VNew();
		void VDestroy();
		StockArticle* VGet(int i);
		void VAdd(StockArticle* sa);
		void VDel(int i);
		void VClear();
		int VSize();
};

#endif // __STOCK_H
