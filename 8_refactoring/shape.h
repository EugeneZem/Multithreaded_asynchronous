#pragma once
//#include <iostream>
#include <string>

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
	std::string name();
	virtual double square();
	virtual double volume();
	virtual double lenght();
	friend double len(point&, point&);
	virtual void shift(int x, int y, int z = 0);
	virtual void scaleX(int);
	virtual void scaleY(int);
	virtual void scaleZ(int);
	virtual void scale(int);
protected:
	std::string _name;
};

class line:public Shape
{
public:
	line(point begin, point end) : _begin(begin), _end(end) { _name = "LINE"; };
	double lenght();
	void shift(int x, int y, int z = 0);
	void scaleX(int);
	void scaleY(int);
	void scale(int);
protected:
	point _begin, _end;
};

class planar_shape : public Shape
{
public:
	planar_shape();
};


class sqr : public planar_shape
{
public:
	sqr(point& a, int len_size_1, int len_size_2);
	double square();
	void shift(int x, int y, int z = 0);
	friend class cube;
	void scaleX(int);
	void scaleY(int);
	void scale(int);
protected:
	point _a, _b, _c, _d;
};

class circle : public planar_shape
{
public:
	circle(const point& centr, int radius);
	double square();
	friend class cylinder;
	void shift(int x, int y, int z = 0);
	void scale(int);
protected:
	point _cntr;
	int _r;
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
	void shift(int x, int y, int z);
	virtual void scaleX(int);
	virtual void scaleY(int);
	virtual void scaleZ(int);
	virtual void scale(int);
protected:
	point _a, _b, _c, _d, _a2, _b2, _c2, _d2;
};

class cylinder : public three_shape
{
public:
	cylinder(const circle& base, int h);
	double volume();
	double square();
	void shift(int x, int y, int z);
	virtual void scaleX(int);
	virtual void scaleY(int);
	virtual void scaleZ(int);
	virtual void scale(int);
protected:
	point _cntr;
	int _h, _r;
};