#ifndef _YYY_POLYGON_H_
#define _YYY_POLYGON_H_

#include <vector>
#include <iostream>
#include <map>
#include "Point.h"
#include "Box.h"

namespace yyy
{
	struct Polygon
	{

		typedef std::vector<Point>::iterator iterator;
		typedef std::vector<Point>::const_iterator const_iterator;

		std::vector<Point> v;
		int id;
		Box box;

		Polygon(int id = -1);
		Polygon(const std::vector<Point> & vec , int id = -1);
		Polygon(std::vector< std::pair<double,double> > vec , int id = -1);

		void update_box(const Point & poi);

		bool inside(const Box & b)const;
		bool cross(const Box & b)const;	//相交
		bool maybe_contain(const Box & b)const;		//也许b在多边形内。
		bool inside_or_cross(const Box & b)const;	//有重合部分
		bool cross_or_inside(const Box & b)const;	//有重合部分

		Point & operator [](int k);
		const Point & operator [](int k)const;

		iterator begin();
		iterator end();
		const_iterator begin()const;
		const_iterator end()const;
		unsigned size()const;

		void push_back(const Point & a);

	};
}

std::ostream & operator << (std::ostream & cout , const yyy::Polygon & a);

#endif //_YYY_POLYGON_H_