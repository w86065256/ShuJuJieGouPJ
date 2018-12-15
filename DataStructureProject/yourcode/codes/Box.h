#ifndef _YYY_BOX_H_
#define _YYY_BOX_H_

namespace yyy
{
	struct Box
	{
		double _v[2][2];
		double & top;
		double & lef;
		double & rig;
		double & bot;

		Box(double t = 0,double l = 0,double b = 0,double r = 0);

		double * operator [](int k);
		const double * operator [](int k)const;

		Box cut(int k,double v)const;
	};

	bool operator == (const Box & a,const Box & b);

	Box cut(const Box & b,int k,double v);
}

#endif //_YYY_BOX_H_