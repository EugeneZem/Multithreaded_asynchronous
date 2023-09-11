#include <iostream>
#include <memory>
#include "shape.h"
#include "transform.h"

void info(std::shared_ptr<Shape> sh)
{
	std::cout << std::endl << sh->name() << std::endl;
	std::cout << "Lenght = " << sh->lenght() << std::endl;
	std::cout << "Square = " << sh->square() << std::endl;
	std::cout << "Volume = " << sh->volume() << std::endl;
}

int main()
{
	point a { 0, 0, 0 };
	point b { 10, 0, 0 };
	point c { 0, 10, 0 };
	point d { 10, 10, 0 };
	int h { 5 };

	std::shared_ptr<Shape> test(new line{ a, b });
	info(test);
	//test->shift(20, 100);
	//info(test);
	test->scale(2);
	info(test);

	test.reset(new sqr{ b, 10, 10 });
	test->shift(-20, -100);
	info(test);
	test->scale(2);
	info(test);
	
	test.reset(new circle{ d, 10 });
	test->shift(-20, -100);
	info(test);
	test->scale(2);
	info(test);

	circle crc{ d, 10 };
	test.reset(new cylinder{ crc, 10 });
	test->shift(-100, -100, -100);
	info(test);

	sqr sq{ a, 1, 1 };
	test.reset(new cube{ sq, 1 });
	test->shift(10, 0, 0);
	info(test);
	test->scale(2);
	info(test);

	return 0;
}
