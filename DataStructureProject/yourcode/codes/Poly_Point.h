#ifndef _YYY_POLY_POINT_H_
#define _YYY_POLY_POINT_H_

#include "Point.h"

namespace yyy
{
	/*
		多边形中的点，k表示在多边形中的编号
	*/
	struct Poly_Point : public Point
	{
		int k;
		Poly_Point(double x = 0,double y = 0,int id = 0,int k = 0);
		Poly_Point(const Point & poi,int id,int k);
		Poly_Point(const Point & poi,int k);
	};
};

#endif //_YYY_POLY_POINT_H_