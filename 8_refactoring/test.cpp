#include <iostream>
#include "shape.h"
#include "transform.h"

int main()
{
	point a { 0, 0, 0 };
	point b { 10, 0, 0 };
	point c { 0, 10, 0 };
	point d { 10, 10, 0 };
	int h { 5 };

	line line1 { a, d };
	std::cout << "Lenght line1 = " << line1.lenght() << std::endl;

	sqr sqr1 { b, 10, 10 };
	std::cout << "Square sqr1 = " << sqr1.square() << std::endl;
	sqr1.shift(0, 100, -100);
	std::cout << "Square sqr1 = " << sqr1.square() << std::endl;

	circle circle1(d, 10);
	std::cout << "Square circle1 = " << circle1.square() << std::endl;
	
	cube cube1 { sqr1, 20 };
	std::cout << "Square cube1 = " << cube1.square() << std::endl;
	std::cout << "Volume cube1 = " << cube1.volume() << std::endl;

	cylinder cylinder1{ circle1, 10 };
	std::cout << "Square cylinder1 = " << cylinder1.square() << std::endl;
	std::cout << "Volume cylinder1 = " << cylinder1.volume() << std::endl;

	return 0;
}
