#include"Polinom.h"

int main()
{
	std::cout << "Select an operation for polinoms from the suggested ones" << std::endl << "+" << std::endl << "+=" << std::endl << "*" << std::endl << "*=" << std::endl;
	while (true)
	{
		TPolinom p1, p2;
		bool flag = true;
		std::string p;
		std::cin >> p;
		if (p == "+")
		{
			TPolinom res;
			std::cout << "p1: ";
			std::cin >> p1;
			std::cout << std::endl << "p2: ";
			std::cin >> p2;
			res = p1 + p2;
			std::cout << std::endl << p1 << " + " << p2 << " = " << res << std::endl;
			flag = false;
		}
		if (p == "+=")
		{
			TPolinom res;
			std::cout << "p1: ";
			std::cin >> p1;
			std::cout << std::endl << "p2: ";
			std::cin >> p2;
			std::cout << std::endl << p1 << " += " << p2 << " = ";
			p1 += p2;
			std::cout << p1 << std::endl;
			flag = false;
		}
		if (p == "*")
		{
			std::cout << "1-multiply by a number" << std::endl << "2-multiply by a monomial" << std::endl << "3-multiply by a polynomial" << std::endl;
			int tmp;
			std::cin >> tmp;
			switch (tmp)
			{
			case(1):
			{
				TPolinom res;
				std::cout << "p:";
				std::cin >> p1;
				std::cout << std::endl << "Number=";
				double val;
				std::cin >> val;
				res = p1 * val;
				std::cout << std::endl << p1 << " * " << val << " = " << res << std::endl;
				break;
			}
			case(2):
			{
				TPolinom res;
				std::cout << "p:";
				std::cin >> p1;
				std::cout << std::endl << "monom=";
				TMonom m;
				std::cin >> m;
				res = p1 * m;
				std::cout << std::endl << p1 << " * " << m << " = " << res << std::endl;
				break;
			}
			case(3):
			{
				TPolinom res;
				std::cout << "p1:";
				std::cin >> p1;
				std::cout << std::endl << "p2:";
				std::cin >> p2;
				res = p1 * p2;
				std::cout << std::endl << p1 << " * " << p2 << " = " << res << std::endl;
				break;
			}
			default:
				break;
			}
			flag = false;
		}
		if (p == "*=")
		{
			TPolinom res;
			std::cout << "p1:";
			std::cin >> p1;
			std::cout << std::endl << "p2:";
			std::cin >> p2;
			std::cout << std::endl << p1 << " *= " << p2 << " = ";
			p1 *= p2;
			std::cout << p1 << std::endl;
			flag = false;
		}
		if (flag)
			break;
	}
	return 0;
}
