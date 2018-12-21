#ifndef _YYY_BOX_H_
#define _YYY_BOX_H_

namespace yyy
{
	struct Box
	{	
		/*
			_v : 
				第一维 ： 0左右 ， 1上下
				第二维 ： 0较小 ， 1较大

			换言之：
				第一维：方向，第二维：左右
				//左儿子更新right , 右儿子更新left
				换言之，我的儿子应更新:[dir][!k]，k是左右

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

		bool inside(const Box & b)const;
	};

	bool operator == (const Box & a,const Box & b);

	Box cut(const Box & b,int k1,int k2,double v);
}

#endif //_YYY_BOX_H_