#include "Box.h"
#include "methods.h"

namespace yyy
{
	Box::Box(double t,double l,double b,double r)
	{ 
		top = _v[1][1];
		lef = _v[0][0];
		bot = _v[0][1];
		rig = _v[1][0];
		top = t;
		lef = l;
		bot = b;
		rig = r;
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
}