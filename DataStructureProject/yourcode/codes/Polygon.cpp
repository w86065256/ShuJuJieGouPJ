#include "Polygon.h"

namespace yyy
{
	Polygon::Polygon(int number)
	{
		num = 0;
	}

	bool Polygon::inside(const Box & b)
	{
		for(auto & p: *this)
		{
			if(!p.inside(b))
				return false;
		}
		return true;
	}
	Polygon::iterator Polygon::begin()
	{
		return v.begin();
	}
	Polygon::iterator Polygon::end()
	{
		return v.end();
	}

	Polygon::const_iterator Polygon::begin()const
	{
		return v.begin();
	}
	Polygon::const_iterator Polygon::end()const
	{
		return v.end();
	}

	unsigned Polygon::size()const
	{
		return v.size();
	}

	Point & Polygon::operator [](int k)
	{
		int n = size();
		k = ((k % n) + n) % n;
		return v[k];
	}

	const Point & Polygon::operator [](int k)const
	{
		int n = size();
		k = ((k % n) + n) % n;
		return v[k];
	}

	void Polygon::push_back(const Point & a)
	{
		v.push_back(a);
	}
}

std::ostream & operator << (std::ostream & cout , const yyy::Polygon & a)
{
	for(auto & p : a)
		cout << "-" << p;
	return cout;
}