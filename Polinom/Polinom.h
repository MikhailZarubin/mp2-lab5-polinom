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
	TMonom();
	bool operator < (const TMonom& m)const;
	bool operator == (const TMonom& m)const;
	bool operator >(const TMonom& m)const;
	TMonom& operator =(const TMonom& m);
	friend std::istream& operator>>(std::istream& in, TMonom& m)
	{
		std::string res;
		in >> res;
		bool flag = false;
		for (unsigned int i = 0; i < res.size(); i++)
		{
			if (res[i] == 'x' || res[i] == 'y' || res[i] == 'z')
			{
				flag = true;
			}
			if (flag)
			{
				if (i + 1 < res.size())
				{
					if (res[i + 1] == '^')
					{
						m.input(res[i], res[i + 2]-'0');
						i += 2;
					}
					else
						m.input(res[i], 1);
				}
				else
					m.input(res[i], 1);

			}
			else
				if (i == 0)
				{
					std::string tmp;
					int j;
					for (j = 0; j < res.size(); j++)
					{
						if (res[j] == 'x' || res[j] == 'y' || res[j] == 'z')
							break;
						tmp += res[j];
					}
					i = j - 1;
					m.coeff = std::stod(tmp);
				}
		}
		return in;
	}
	friend std::ostream& operator << (std::ostream& out, const TMonom& m)
	{
		if(m.coeff!=1.0)
		out << m.coeff;
		if (m.x + m.y + m.z)
		{
			if (m.coeff != 1.0 && m.x)
				out << '*';
			out << m.print('x', m.x);
			if (m.y)
				out << '*';
			out << m.print('y', m.y);
			if (m.z)
				out << '*';
			out<< m.print('z', m.z);
		}
		return out;
	}
	std::string print(char p, int pow) const;
	void input(char p, int val);
};
TMonom::TMonom()
{
	 x = y = z = 0;
	 coeff = 1.0;
}
void TMonom::input(char p, int val)
{
	switch (p)
	{
	case 'x':x = val;
		break;
	case'y':y = val;
		break;
	case'z':z = val;
		break;
	}
}
std::string TMonom:: print(char p, int pow) const
{
	std::string res="";
	if (pow != 0)
	{
		if (pow > 1)
		{
			res += p;
			res += '^';
			res += std::to_string(pow);
		}
		else
		{
			res += p;
		}
	}
	return res;
}
bool TMonom::operator <(const TMonom& m) const
{
	int sum = x + y + z;
	int sum_m = m.x + m.y + m.z;
	return (sum < sum_m) ? true : false;
}
bool TMonom::operator >(const TMonom& m) const
{
	int sum = x + y + z;
	int sum_m = m.x + m.y + m.z;
	return (sum > sum_m) ? true : false;
}
bool TMonom::operator == (const TMonom& m) const
{
	return x == m.x && y == m.y && z == m.z;
}
TMonom& TMonom::operator =(const TMonom& m)
{
	coeff = m.coeff;
	x = m.x;
	y = m.y;
	z = m.z;
	return *this;
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
	void Reset() { pCurr = pFirst; }
	bool IsEnd() {if (size != 0) return pCurr == pStop; return true;}
	void GoNext() { pPrev = pCurr; pCurr = pCurr->pNext; }
	friend std::istream& operator >> (std::istream& in, TList<T>& list)
	{
		std::cout << "size=";
		int t;
		in >> t;
		if (t < 0)
			throw 0;
		for (int i = 0; i < t; i++)
		{
			T tmp;
			in >> tmp;
			list.InsLast(tmp);
		}
		return in;
	}
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
	if (size==0)
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
	if (size==0)
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
	if (size==0)
		throw 0;
	else
	{
		TLink<T>* t = pFirst->pNext;
		delete pFirst;
		pFirst = t;
		size--;
	}
}
template <class T>
void TList<T>::DelCurr()
{
	if (size==0)
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
	if (size==0)
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
template<class T>
class THeadList : public TList<T> {
protected:
	TLink<T>* pHead;
public:
	THeadList();
	THeadList(const THeadList& h);
	~THeadList();
	void InsFirst(T elem);
	void DelFirst();
	void InsLast(T elem);
	void InsCurr(T elem);
};
template<class T>
THeadList<T>::THeadList() : TList<T>()
{
	pHead = new TLink<T>;
	TList<T>::pStop = pHead;
	pHead->pNext = TList<T>::pStop;
}
template<class T>
THeadList<T>::THeadList(const THeadList<T>& h) :TList<T>(h)
{
	pHead = new TLink<T>;
	pHead->pNext = TList<T>::pFirst;
}
template<class T>
THeadList<T>::~THeadList()
{
	TList<T>::~TList();
	delete pHead;
}
template<class T>
void THeadList<T>::InsFirst(T elem)
{
	TList<T>::InsFirst(elem);
	pHead->pNext = TList<T>::pFirst;
}
template <class T>
void THeadList<T>::DelFirst()
{
	TList<T>::DelFirst();
	pHead->pNext = TList<T>::pFirst;
}
template<class T>
void THeadList<T>::InsLast(T elem)
{
	if (TList<T>::size == 0)
		InsFirst(elem);
	else
		TList<T>::InsLast(elem);
}
template<class T>
void THeadList<T>::InsCurr(T elem)
{
	if (TList<T>::size == 0)
	{
		InsFirst(elem);
	}
	else
		TList<T>::InsCurr(elem);
}
class TPolinom :public THeadList<TMonom>{
public:
	TPolinom();
	TPolinom(const TPolinom& p);
	void InsMonom(const TMonom& m);
	TPolinom& operator += (TPolinom& p);
	friend std::istream& operator >> (std::istream& in, TPolinom& p)
	{
		std::cout << "size=";
		int t;
		in >> t;
		if (t < 0)
			throw 0;
		for (int i = 0; i < t; i++)
		{
			TMonom m;
			in >> m;
			p.InsMonom(m);
		}
		return in;
	}
};
TPolinom::TPolinom() :THeadList<TMonom>()
{
	TMonom tmp;
	tmp.z = -1;
	tmp.coeff = 0.0;
	pHead->val = tmp;
}
TPolinom::TPolinom(const TPolinom& p) : THeadList<TMonom>(p)
{
	pHead->val = p.pHead->val;
}
void TPolinom::InsMonom(const TMonom& m)
{
	for (Reset(); !IsEnd(); GoNext())
	{
		if (pCurr->val < m)
		{
			InsCurr(m);
			break;
		}
		if (pCurr->val == m)
		{
			if (pCurr->val.coeff + m.coeff != 0)
				pCurr->val.coeff += m.coeff;
			else
				DelCurr();
			break;
		}
	}
	if (IsEnd())
		InsLast(m);
}
TPolinom& TPolinom::operator+=(TPolinom& p)
{
	p.Reset();
	for (Reset(); !IsEnd(); GoNext())
	{
		if (pCurr->val < p.pCurr->val)
		{
			InsCurr(p.pCurr->val);
			p.GoNext();
			if (p.IsEnd())
				break;
		}
		if (p.pCurr->val == pCurr->val)
		{
			double tmp = p.pCurr->val.coeff + pCurr->val.coeff;
			if (tmp)
				pCurr->val.coeff = tmp;
			else
			{
				DelCurr();
			}
			p.GoNext();
			if (IsEnd())
				break;
		}
	}
		while (!p.IsEnd())
		{
			InsLast(p.pCurr->val);
			p.GoNext();

		}
		return *this;
}