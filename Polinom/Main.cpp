#include"Polinom.h"

int main()
{
	TPolinom p1, p2;
	std::cin >> p1;
	std::cin >> p2;
	std::cout << "p1:" << std::endl << p1 << std::endl << "p2:" << std::endl << p2 << std::endl;
	TMonom m;
	m.x = 2;
	m.y = 3;
	m.coeff = 5.0;
	p1.InsMonom(m);
	std::cout << "p1:" << std::endl << p1 << std::endl;
	p1 += p2;
	std::cout << "p1" << std::endl << p1 << std::endl << "___________________________" << std::endl;
	std::cout << "p1:" << std::endl << p1 << std::endl << "p2:" << std::endl << p2 << std::endl;
	TPolinom p3;
	p3 = p1 * p2;
	std::cout << "p3:" << std::endl << p3 << std::endl;
	return 0;
}