#pragma once
#include<iostream>
#include<string>
template <class T>
struct TLink {
	T val;
	TLink<T>* pNext;
};
struct TMonom
{
	double coeff;
	int x, y, z;
	bool operator < (const TMonom& m);
	/*friend std::istream& operator>>(std::istream& in, TMonom& m)
	{

	}
	friend std::ostream& operator<< (std::ostream& out, const TMonom& m)
	{

	}*/
};
bool TMonom::operator <(const TMonom& m)
{
	int sum = x + y + z;
	int sum_m = m.x + m.y + m.z;
	return (sum < sum_m) ? true : false;
}
template <class T>
class TList {
protected:
	TLink<T>* pFirst, * pLast, * pCurr, * pPrev, * pStop;
	int size, pos;
public:
	TList();
	TList(const TList& list);
	~TList();
	void InsFirst(T elem);
	void InsLast(T elem);
	void DelFirst();
	void DelCurr();
	void InsCurr(T elem);
	/*friend std::istream& operator >> (std::istream& in, TList<T>& list)
	{
		T elem;
		int iter = 0;
		TLink<T>* curr=NULL;
		while (in >> elem)
		{
			std::cout << "Press enter to leave the input";
			std::cout << "Elem number " << iter << " =";
			if (iter == 0)
			{
				list.InsFirst(elem);
				curr = list.pFirst;
				iter++;
			}
			else
			{
				TLink<T>* t = new TLink<T>;
				t->val = elem;
				t->pNext = list.pStop;
				curr->pNext = t;
				list.pLast = t;
				curr = t;
				iter++;
			}
			size++;
		}
		return in;
	}*/
	friend std::ostream& operator<<(std::ostream& out, const TList<T> list) 
	{
		TLink<T>* t = list.pFirst;
		while (t != list.pStop)
		{
			out << t->val << ' ';
			t = t->pNext;
		}
		return out;
	}
};
template<class T>
TList<T>::TList()
{
	pStop = NULL;
	pFirst = pLast = pCurr = pPrev = pStop;
	size = 0;
	pos = 0;
}
template<class T>
TList<T>::TList(const TList<T>& list)
{
	if (list.size == 0)
	{
		pStop = list.pStop;
		pFirst = pLast = pCurr = pPrev = pStop;
		size = 0;
		pos = 0;
	}
	else
	{
		pStop = list.pStop;
		pCurr = pPrev = pStop;
		pos = 0;
		TLink<T>* prev = new TLink<T>;
		prev->val = list.pFirst->val;
		prev->pNext = pStop;
		pFirst = prev;
		TLink<T>* curr = list.pFirst;
		while (curr->pNext != pStop)
		{
			curr = curr->pNext;
			TLink<T>* link = new TLink<T>;
			link->val = curr->val;
			link->pNext = pStop;
			prev->pNext = link;
			prev = link;
		}
		size = list.size;
		pLast = prev;
	}
}
template<class T>
TList<T>::~TList()
{
	pCurr = pPrev = pStop;
	size = 0;
	pos = 0;
	while (pFirst != pStop)
	{
		TLink<T>* curr = pFirst->pNext;
		delete pFirst;
		pFirst = curr;
	}
	pLast = pStop;
}
template<class T>
void TList<T>::InsFirst(T elem)
{
		TLink<T>* tmp = new TLink<T>;
		tmp->val = elem;
	if (pFirst == pStop)
	{
		tmp -> pNext = pStop;
		pFirst = pLast = tmp;
	}
	else
	{
		tmp->pNext = pFirst;
		pFirst = tmp;
	}
	size++;
}
template<class T>
void TList<T>::InsLast(T elem)
{
	TLink<T>* tmp = new TLink<T>;
	tmp->val = elem;
	tmp->pNext = pStop;
	if (pFirst == pStop)
	{
		pFirst = pLast = tmp;
	}
	else
	{
		pLast->pNext = tmp;
		pLast = tmp;
	}
	size++;
}
template<class T>
void TList<T>::DelFirst()
{
	if (pFirst == pStop)
		throw 0;
	else
	{
		TLink<T>* t = pFirst->pNext;
		delete pFirst;
		pFirst = t;
		size--;
		if (size == 0)
			pLast = pStop;
	}
}
template <class T>
void TList<T>::DelCurr()
{
	if (pCurr == pStop)
		throw 0;
	if (pCurr == pFirst)
		DelFirst();
	else
	{
		pPrev->pNext = pCurr->pNext;
		delete pCurr;
		pCurr = pPrev->pNext;
		size--;
	}
}
template<class T>
void TList<T>::InsCurr(T elem)
{
	if (pCurr == pStop)
		InsLast(elem);
	else
	{
		if (pCurr == pFirst)
			InsFirst(elem);
		else
		{
			TLink<T>* t = new TLink<T>;
			pPrev->pNext = t;
			t->val = elem;
			t->pNext = pCurr;
			pPrev = t;
			size++;
		}
	}
}
