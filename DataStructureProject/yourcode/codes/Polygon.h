#ifndef _YYY_POLYGON_H_
#define _YYY_POLYGON_H_

#include <vector>
#include <iostream>
#include "Point.h"
#include "Box.h"

namespace yyy
{
	struct Polygon
	{

		typedef std::vector<Point>::iterator iterator;
		typedef std::vector<Point>::const_iterator const_iterator;

		std::vector<Point> v;
		int num;

		Polygon(int number = -1);

		bool inside(const Box & b);

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