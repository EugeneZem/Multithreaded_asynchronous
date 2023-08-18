#include <iostream>
#include "Data.h"

int main()
{
	Data a { 2 };
	Data b { 20 };
	Data c { 20.55 };
	Data d { 5.69 };
	Data e { "qwerty" };
	Data f { "QWERTY" };

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "f = " << f << std::endl << std::endl;

	swap(a, b);
	swap(c, d);
	swap(e, f);

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "f = " << f << std::endl;
}