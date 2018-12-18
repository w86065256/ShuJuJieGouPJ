#include "Point.h"
#include "methods.h"
#include "Polygon.h"

namespace yyy
{
	Point::Point(double x,double y , int id)
	{
		this->x = x;
		this->y = y;
		this->id = id;
	}

	Point::Point( std::pair<double,double> p , int id)
	{
		this->x = p.first;
		this->y = p.second;
		this->id = id;
	}

	double & Point::operator [](int k)
	{
		if(k == 0)
			return x; 
		if(k == 1)
			return y;
		throw "Point.operator[] : bad index";
	}

	double Point::operator [](int k)const
	{
		if(k == 0)
			return x; 
		if(k == 1)
			return y;
		throw "Point.operator[] : bad index";
	}

	Point & Point::operator += (const Point & v)
	{
		x += v.x;
		y += v.y;
	}	

	Point & Point::operator -= (const Point & v)
	{
		x -= v.x;
		y -= v.y;
	}

	Point & Point::operator *= (double v )
	{
		x *= v;
		y *= v;
	}

	Point & Point::operator /= (double v )
	{
		x /= v;
		y /= v;
	}

	Point operator + (const Point & a,const Point & b)
	{
		return Point(a.x + b.x , a.y + b.y);
	}
	Point operator - (const Point & a,const Point & b)
	{
		return Point(a.x - b.x , a.y - b.y);
	}
	Point operator * (const Point & a,double v)
	{
		return Point(a.x * v , a.y * v);
	}
	Point operator / (const Point & a,double v)
	{
		return Point(a.x / v , a.y / v);
	}

	double operator * (const Point & a,const Point & b)
	{//叉乘
		return cross_mul(a,b);
	}
	double operator ^ (const Point & a,const Point & b)
	{//点乘
		return point_mul(a,b);
	}

	bool operator < (const Point & a,const Point & b)
	{
		if(a.x < b.x)
			return true;
		if(b.x < a.x)
			return false;
		return a.y < b.y;
	}
	bool operator <= (const Point & a,const Point & b)
	{
		if(a.x < b.x)
			return true;
		if(b.x < a.x)
			return false;
		return a.y <= b.y;
	}
	bool operator > (const Point & a,const Point & b)
	{
		if(a.x > b.x)
			return true;
		if(b.x > a.x)
			return false;
		return a.y > b.y;
	}
	bool operator >= (const Point & a,const Point & b)
	{
		if(a.x > b.x)
			return true;
		if(b.x > a.x)
			return false;
		return a.y >= b.y;
	}
	bool operator == (const Point & a,const Point & b)
	{
		return EQU(a.x , b.x) && EQU(a.y , b.y);
	}
	bool operator != (const Point & a,const Point & b)
	{
		return ! (a == b);
	}
	bool Point::is_same(const Point & p)const
	{
		return id == p.id;
	}

	bool is_same(const Point & a,const Point & b)
	{
		return a.id == b.id;
	}

	bool Point::inside(const Box & b)const
	{
		return b.lef <= x && x <= b.rig && b.bot <= y && y <= b.top;
	}
	
	bool Point::inside(const Polygon & b , int max_test)const
	{
		const Point & p = *this;
		int res[2] = {0,0,};
		for(int k = 1;k <= max_test;k++)
		{//k : 实验次数
			int cnt = 0;	//cnt : 交叉次数 (mod 2)
			Point q( (rand_double() + 1) * 1e9 , (rand_double() + 1) * 1e9);
			for(int i = 0;i < b.size();i++)
			{
				if(k == 1)
				{//判断是否在边缘上，若在，返回false
					if(on(b[i] , b[i+1] , p))
						return false;
				}

				if(cross(p,q,b[i],b[i+1]))
					cnt ^= 1;
			}
			res[cnt] ++;
		}
		//奇数次数较多
		return res[1] > res[0];
	}

	/* BAD , but fast
	bool Point::inside(const Polygon & b)const
	{
		const Point & P = *this;
		int cnt[2] = {0,0,};
		for(int i = 0;i < b.size();i++)
		{
			const Point & P1 = b[i];
			const Point & P2 = b[i+1];

			//点在边缘上，不在多边形内
			if(on(b[i] , b[i+1] , P))
				return false;

			for(int u = 0;u <= 1;u++)
			{
				if
				( 
					(P1[u] - P[u]) * (P2[u] - P[u]) <= 0 				//分在两侧
					and not (EQU(P2[u] , P[u]) && !EQU(P1[u] , P[u])) 	//若不同在线上，P2要取开
					and (P2-P) * (P1-P) * (P2[u] - P1[u]) > 0			//P1-P2靠右者在靠左者的顺时针方向
				)
				cnt[u] ++;
			}
		}

		//奇数次说明在内，返回true
		return ((cnt[0] & 1) == 1) && ((cnt[1] & 1) == 1);
	}
	*/
}

std::ostream & operator << (std::ostream & cout , const yyy::Point & a)
{
	return cout << "(" << a.x << "," << a.y << ")";
}