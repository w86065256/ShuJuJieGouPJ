#include "Polygon.h"
#include "methods.h"

namespace yyy
{
	Polygon::Polygon(int id)
	{
		this->id = id;
		this->box = Box(-INF , INF , INF , -INF);
	}

	Polygon::Polygon(const std::vector<Point> & vec , int id)
	{
		v = vec;
		this->id = id;
		for(int i = 0;i < vec.size();i++)
			update_box(vec[i]);
	}
	Polygon::Polygon(std::vector< std::pair<double,double> > vec , int id)
	{
		for(int i = 0;i < vec.size();i++)
			v.push_back( Point(vec[i]) );

		for(int i = 0;i < vec.size();i++)
			update_box(v[i]);

		this->id = id;
	}

	void Polygon::update_box(const Point & poi)
	{
		box.bot = std::min(box.bot , poi.y);
		box.top = std::max(box.top , poi.y);
		box.lef = std::min(box.lef , poi.x);
		box.rig = std::max(box.rig , poi.x);
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

	bool Polygon::maybe_contain(const Box & b)const
	{
		return b.inside(box);
	}

	bool Polygon::inside_or_cross(const Box & b)const
	{
		return inside(b) or cross(b) or maybe_contain(b);
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
		update_box(a);
	}
	
	bool Polygon::cross(const Box & b)const
	{
		const Polygon & p = *this;
		for(int i = 0;i < size();i++)
		{
			for(int u = 0;u <= 1;u++)
			{
				if(	b[u^1][0] <= p[i  ][u^1] && p[i  ][u^1] <= b[u^1][1] || 
					b[u^1][0] <= p[i+1][u^1] && p[i+1][u^1] <= b[u^1][1] )
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