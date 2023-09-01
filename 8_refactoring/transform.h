#pragma once
#include"shape.h"
class transform
{
public:
	transform(const Shape& sh);
	//Shape shift(int x, int y, int z = 0);
	//Shape scaleX(int a);
	//Shape scaleY(int d);
	//Shape scaleZ(int e);
	//Shape scale(int s);

private:
	Shape shape;
};