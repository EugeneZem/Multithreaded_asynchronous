#define _USE_MATH_DEFINES
#include"shape.h"
#include<cmath>

Shape::Shape() {}

void Shape::shift(int x, int y, int z) {}

double Shape::square() { return 0; }

double Shape::volume() { return 0; }

planar_shape::planar_shape() {}

double len(const point& a, const point& b)
{
	int lx = a._x - b._x;
	int ly = a._y - b._y;
	int lz = a._z - b._z;
	double result = sqrt(pow(lx, 2) + pow(ly, 2) + pow(lz, 2));
	return result;
}

double line::lenght()
{
	double result = len(_begin, _end);
	return result;
}

void line::shift(int x, int y, int z)
{
	_begin._x += x;
	_begin._y += y;
	_begin._z += z;
	_end._x += x;
	_end._y += y;
	_end._z += z;
}

sqr::sqr(point& a, int len_size_1, int len_size_2)
{
	_a = a;
	_b = _a;
	_b._x += len_size_1;
	_c = _a;
	_c._y += len_size_2;
	_d = _a;
	_d._x += len_size_1;
	_d._y += len_size_2;
}


double sqr::square()
{
	double len_size_1 = len(_a, _b);
	double len_size_2 = len(_a, _c);
	double result = len_size_1 * len_size_2;
	return result;
}

circle::circle(point centr, int radius) : _cntr(centr), _r(radius) {};

double circle::square()
{
	double result = M_PI * _r * _r / 2;
	return result;
}

three_shape::three_shape() {}

point extrude(const point& pnt, int h)
{
	point result = pnt;
	result._z += h;
	return result;
}

cube::cube(const sqr& base, int h)
{
	_a = base._a;
	_b = base._b;
	_c = base._c;
	_d = base._d;
	_a2 = extrude(_a, h);
	_b2 = extrude(_b, h);
	_c2 = extrude(_c, h);
	_d2 = extrude(_d, h);
};

double cube::square()
{
	double len_size_1 = len(_a, _b);
	double len_size_2 = len(_a, _b);
	double len_size_3 = len(_a, _a2);
	double result = (len_size_1 * len_size_2 + len_size_1 * len_size_3 + len_size_2 * len_size_3) * 2;
	return result;
}

double cube::volume()
{
	double len_size_1 = len(_a, _b);
	double len_size_2 = len(_a, _b);
	double len_size_3 = len(_a, _a2);
	double result = len_size_1 * len_size_2 * len_size_3;
	return result;
}


cylinder::cylinder(const circle& base, int h)
{
	_cntr = base._cntr;
	_r = base._r;
	_h = h;
}

double cylinder::volume()
{
	double result = (M_PI * _r * _r / 2) * _h;
	return result;
}

double cylinder::square()
{
	double result = (M_PI * _r * _r / 2) * 2 + 2 * M_PI * _r * _h;
	return result;
}