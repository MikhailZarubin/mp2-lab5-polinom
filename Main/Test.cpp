#include"../Polinom/Polinom.h"

int main()
{
	TList<int> list;
	list.InsFirst(10);
	list.InsFirst(10);
	list.InsFirst(10);
	list.InsFirst(1);
	list.InsLast(102);
	list.DelFirst();
	std::cout << list;
	return 0;
}