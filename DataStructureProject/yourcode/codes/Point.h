#ifndef _YYY_POINT_H_
#define _YYY_POINT_H_

#include <iostream>
#include <map>

#include "Box.h"

namespace yyy
{
	struct Polygon;

	struct Point
	{
		double x;
		double y;
		int id;

		Point(double x = 0,double y = 0 , int id = -1);
		Point( std::pair<double,double> p , int id = -1);
		
		double & operator [](int k);
		double operator [](int k)const;

		Point & operator += (const Point & v);
		Point & operator -= (const Point & v);
		Point & operator *= (double v );
		Point & operator /= (double v );

		bool inside(const Box & b)const;
		bool inside(const Polygon & b , int max_test = 3)const;

		bool is_same(const Point & p)const;	//编号相同
	};

	Point operator + (const Point & a,const Point & b);
	Point operator - (const Point & a,const Point & b);
	Point operator * (const Point & a,double v);
	Point operator / (const Point & a,double v);
	double operator * (const Point & a,const Point & b);
	double operator ^ (const Point & a,const Point & b);
	bool operator < (const Point & a,const Point & b);
	bool operator <= (const Point & a,const Point & b);
	bool operator > (const Point & a,const Point & b);
	bool operator >= (const Point & a,const Point & b);
	bool operator == (const Point & a,const Point & b);
	bool operator != (const Point & a,const Point & b);
	bool is_same(const Point & a,const Point & b);	//编号相同

	typedef Point Vector;
}


std::ostream & operator << (std::ostream & cout , const yyy::Point & a);

#endif //_YYY_POINT_H_