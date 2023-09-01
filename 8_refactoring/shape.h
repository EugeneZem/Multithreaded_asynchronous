#pragma once

class point	
{
public:
	point() : _x(0), _y(0), _z(0) {};
	point(int x, int y, int z) : _x(x), _y(y), _z(z) {};
	int _x, _y, _z;
};

class Shape
{
public:
	Shape();
	virtual double square();
	virtual double volume();
	friend double len(point&, point&);
	virtual void shift(int x, int y, int z);
protected:
	const int _type = 2;
};

class planar_shape : public Shape
{
public:
	planar_shape();
};

class line:public Shape
{
public:
	line(point begin, point end) : _begin(begin), _end(end) {};
	double lenght();
	void shift(int x, int y, int z);
protected:
	point _begin, _end;
	const int _type = 0;
};

class sqr : public planar_shape
{
public:
	sqr(point& a, int len_size_1, int len_size_2);
	double square();
//	void shift(int x, int y, int z);
	friend class cube;
protected:
	point _a, _b, _c, _d;
	const int _type = 1;
};

class circle : planar_shape
{
public:
	circle(point centr, int radius);
	double square();
	friend class cylinder;
protected:
	point _cntr;
	int _r;
	const int _type = 3;

};
 
class three_shape : public Shape
{
public:
	three_shape();
	friend point extrude(const point& pnt, int h);
protected:
};

 
class cube : public three_shape
{
public:
	cube(const sqr& base, int h);
	double volume();
	double square();
protected:
	point _a, _b, _c, _d, _a2, _b2, _c2, _d2;
	const int _type = 2;
};

class cylinder : public three_shape
{
public:
	cylinder(const circle& base, int h);
	double volume();
	double square();
protected:
	point _cntr;
	int _h, _r;
	const int _type = 4;
};