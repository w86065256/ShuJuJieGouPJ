#include "Point.h"
#include "methods.h"
#include "Polygon.h"

namespace yyy
{
	Point::Point(double x,double y , int number)
	{
		this->x = x;
		this->y = y;
		num = number;
	}

	double & Point::operator [](int k)
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
	
}

std::ostream & operator << (std::ostream & cout , const yyy::Point & a)
{
	return cout << "(" << a.x << "," << a.y << ")";
}