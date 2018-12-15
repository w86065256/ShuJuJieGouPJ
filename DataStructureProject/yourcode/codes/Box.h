#ifndef _YYY_BOX_H_
#define _YYY_BOX_H_

namespace yyy
{
	struct Box
	{	
		/*
			_v : 
				第一维 ： 0左右 ， 1上下
				第二位 ： 0较小 ， 1较大
		*/
		double _v[2][2];
		double & top;
		double & lef;
		double & rig;
		double & bot;

		Box(double t = 0,double l = 0,double b = 0,double r = 0);

		Box & operator = (const Box & b);

		double * operator [](int k);
		const double * operator [](int k)const;

		Box cut(int k1,int k2,double v)const;
	};

	bool operator == (const Box & a,const Box & b);

	Box cut(const Box & b,int k1,int k2,double v);
}

#endif //_YYY_BOX_H_