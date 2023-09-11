#define _USE_MATH_DEFINES
#include"shape.h"
#include<cmath>

//-----------------------------------------------
// Shape

Shape::Shape() {}

double Shape::square() { return 0; }

double Shape::volume() { return 0; }

double Shape::lenght() { return 0; }

void Shape::shift(int x, int y, int z) {}

void Shape::scaleX(int) {}

void Shape::scaleY(int) {}

void Shape::scaleZ(int) {}

void Shape::scale(int) {}

std::string Shape::name()
{
	return _name;
}

planar_shape::planar_shape() {}

//-----------------------------------------------
// line

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

void line::scaleX(int s) { _end._x = _begin._x + (_end._x - _begin._x) * s; }

void line::scaleY(int s) { _end._y = _begin._y + (_end._y - _begin._y) * s; }

//void line::scaleZ(int s) { _end._z *= s; }

void line::scale(int s) 
{
	_end._x = _begin._x + (_end._x - _begin._x) *  s;
	_end._y = _begin._y + (_end._y - _begin._y) * s;
	_end._z = _begin._x + (_end._z - _begin._z) * s;
}

//-----------------------------------------------
// sqr

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
	_name = "SQR";
}

void sqr::shift(int x, int y, int z)
{
	_a._x += x; _a._y += y; _a._z += z;
	_b._x += x; _b._y += y; _b._z += z;
	_c._x += x; _c._y += y; _c._z += z;
	_d._x += x; _d._y += y; _d._z += z;
}


double sqr::square()
{
	double len_size_1 = len(_a, _b);
	double len_size_2 = len(_a, _c);
	double result = len_size_1 * len_size_2;
	return result;
}

void sqr::scaleX(int s) 
{
	_b._x = _a._x + (_b._x - _a._x) * s;
	_d._x = _b._x;
}

void sqr::scaleY(int s)
{
	_c._y = _a._y + (_c._y - _a._y) * s;
	_d._y = _c._y;
}

void sqr::scale(int s)
{
	_b._x = _a._x + (_b._x - _a._x) * s;
	_d._x = _b._x;
	_c._y = _a._y + (_c._y - _a._y) * s;
	_d._y = _c._y;
}

//-----------------------------------------------
// circle

circle::circle(const point& centr, int radius) : _cntr(centr), _r(radius) { _name = "CIRCLE"; };

double circle::square()
{
	double result = M_PI * _r * _r / 2;
	return result;
}

void circle::shift(int x, int y, int z)
{
	_cntr._x += x; _cntr._y += y; _cntr._z += z;
}

three_shape::three_shape() {}

point extrude(const point& pnt, int h)
{
	point result = pnt;
	result._z += h;
	return result;
}

void circle::scale(int s) { _r *= s; }

//-----------------------------------------------
// cube

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
	_name = "CUBE";
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

void cube::shift(int x, int y, int z)
{
	_a._x += x; _a._y += y; _a._z += z;
	_a2._x += x; _a2._y += y; _a2._z += z;
	_b._x += x; _b._y += y; _b._z += z;
	_b2._x += x; _b2._y += y; _b2._z += z;
	_c._x += x; _c._y += y; _c._z += z;
	_c2._x += x; _c2._y += y; _c2._z += z;
	_d._x += x; _d._y += y; _d._z += z;
	_d2._x += x; _d2._y += y; _d2._z += z;
}

void cube::scaleX(int s)
{
	_b._x = _a._x + (_a._x - _b._x) * s;
	_b2._x = _a2._x + (_a2._x - _b2._x) * s;
	_d._x = _a._x + (_a._x - _d._x) * s;
	_d2._x = _d2._x + (_a2._x - _d2._x) * s;
}

void cube::scaleY(int s)
{
	_c._y = _a._y + (_a._y - _c._y) * s;
	_c2._y = _a2._y + (_a2._y - _c2._y) * s;
	_d._y = _a._y + (_a._y - _d._y) * s;
	_d2._y = _d2._y + (_a2._y - _d2._y) * s;
}

void cube::scaleZ(int s)
{	
	_a2._z = _a._z + (_a2._z - _a._z) * s;
	_b2._z = _b._z + (_b2._z - _b._z) * s;
	_c2._z = _c._z + (_c2._z - _c._z) * s;
	_d2._z = _d._z + (_d2._z - _d._z) * s;
}

void cube::scale(int s)
{
	scaleX(s);
	scaleY(s);
	scaleZ(s);
}

cylinder::cylinder(const circle& base, int h)
{
	_cntr = base._cntr;
	_r = base._r;
	_h = h;
	_name = "CYLINDER";
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

void cylinder::shift(int x, int y, int z)
{
	_cntr._x += x; _cntr._y += y; _cntr._z += z;
}

void  cylinder::scaleX(int s)
{
	_r *= s;
}

void  cylinder::scaleY(int s)
{
	_r *= s;
}

void  cylinder::scaleZ(int s)
{
	_h *= s;
}

void cylinder::scale(int s)
{
	_r *= s;
	_h *= s;
}