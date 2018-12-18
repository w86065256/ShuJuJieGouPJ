#include "Polygon.h"

namespace yyy
{
	Polygon::Polygon(int id)
	{
		this->id = id;
	}

	Polygon::Polygon(const std::vector<Point> & vec , int id)
	{
		v = vec;
		this->id = id;
	}
	Polygon::Polygon(std::vector< std::pair<double,double> > vec , int id)
	{
		for(int i = 0;i < vec.size();i++)
			v.push_back( Point(vec[i]) );
		this->id = id;
	}

	bool Polygon::inside(const Box & b)const
	{
		for(const auto & p: *this)
		{
			if(!p.inside(b))
				return false;
		}
		return true;
	}

	bool Polygon::inside_or_cross(const Box & b)const
	{
		return inside(b) or cross(b);
	}
	bool Polygon::cross_or_inside(const Box & b)const
	{
		return inside_or_cross(b);
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
	
	bool Polygon::cross(const Box & b)const
	{
		const Polygon & p = *this;
		for(int i = 0;i < size();i++)
		{
			for(int u = 0;u <= 1;u++)
			{
				if(	b[u^1][0] <= p[i  ][u^1] && p[i  ][u^1] <= b[u^1][1] && 
					b[u^2][0] <= p[i+1][u^1] && p[i+1][u^1] <= b[u^1][1] )
				{
					if( (p[i][u] - b[u][0]) * (p[i+1][u] - b[u][0]) < 0 || 
						(p[i][u] - b[u][1]) * (p[i+1][u] - b[u][1]) < 0 )
						return true;
				}
			}
		}
		return false;
	}
}

std::ostream & operator << (std::ostream & cout , const yyy::Polygon & a)
{
	for(auto & p : a)
		cout << "-" << p;
	return cout;
}