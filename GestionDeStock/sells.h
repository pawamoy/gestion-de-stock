#ifndef __SELLS_H
#define __SELLS_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <QByteArray>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "article.h"

class SeVector
{
	public:
		SeVector();
		~SeVector();
		SoldArticle* Get(int i);
		void Add(SoldArticle* sa);
		void Del(int i);
		void Clear();
		int Size();
		
		bool Empty();
	
	private:
		std::vector<SoldArticle*>* sells;
};

class Sells
{
	public:
		Sells();
		~Sells();
		
        void ReadSellsFile(QString path);
        void WriteSellsFile(QString path);
        void Print(SoldArticle* sa);
        void PrintOne(int i);
        void PrintAll();
		
		SoldArticle* GetArticleN(int i);
		int GetPosition(SoldArticle* sa);
		// first occurence
		SoldArticle* GetArticle(int ref);
		SoldArticle* GetArticle(Ref ref);
		SoldArticle* GetArticle(SoldArticle sa);
		// all occurences (remember to destroy result after treatment)
		SeVector GetArticles(int ref);
		SeVector GetArticles(Ref ref);
		SeVector GetArticles(SoldArticle sa);
        int GetSellsSize();
        StockArticle ToStock(SoldArticle* sa);
		
		void ClearSells();
        // error if all infos are not provided
		void New(SoldArticle* sa);
        void New(int r, int q, float bp, float sp, int di, QDate de, QDate se=QDate::currentDate());
        void New(Ref r, int q, float bp, float sp, int di, QDate de, QDate se=QDate::currentDate());
		
		bool Contains(int reference);
		bool Contains(Ref reference);
		bool Contains(SoldArticle sa);
		bool Contains(SoldArticle* sa);
		
	private:
		SeVector sells;
		
		// vector operations
		SeVector VNew();
		void VDestroy();
		SoldArticle* VGet(int i);
		void VAdd(SoldArticle* sa);
		void VDel(int i);
		void VClear();
		int VSize();
};

#endif // __SELLS_H
