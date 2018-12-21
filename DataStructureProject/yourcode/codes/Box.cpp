#include "Box.h"
#include "methods.h"

namespace yyy
{
	Box::Box(double t,double l,double b,double r):
		top(_v[1][1]),lef(_v[0][0]),bot(_v[1][0]),rig(_v[0][1])
	{ 
		top = t;
		lef = l;
		bot = b;
		rig = r;
	}

	Box & Box::operator = (const Box & b)
	{
		for(int i = 0;i <= 1;i++)
		{
			for(int j = 0;j <= 1;j++)
			{
				_v[i][j] = b._v[i][j];
			}
		}
		return *this;
	}

	bool operator == (const Box & a,const Box & b)
	{
		return EQU(a.top , b.top) && EQU(a.lef , b.lef) && EQU(a.bot , b.bot) && EQU(a.rig , b.rig);
	}

	double * Box::operator [](int k)
	{
		return _v[k];
	}

	const double * Box::operator [](int k)const
	{
		return _v[k];
	}

	Box Box::cut(int k1,int k2,double v)const
	{
		return yyy::cut(*this,k1,k2,v);
	}

	Box cut(const Box & b,int k1,int k2,double v)
	{
		Box a = b;
		a[k1][k2] = v;
		return a;
	}
	
	bool Box::inside(const Box & b)const
	{
		return 	b.lef <= lef && rig <= b.rig && 
				b.bot <= bot && top <= b.top;
	}
}