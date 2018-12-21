#ifndef _YYY_METHODS_H_
#define _YYY_METHODS_H_

#include <stdlib.h>
#include "Box.h"
#include "Point.h"

namespace yyy
{
	struct Box;
	struct KDTNode;

	const double EPS = 1e-9;
	const double INF = 1e9;
	const double DEFUALT_ALPHA = .75;

	const Box MAX_BOX = Box(INF , -INF , -INF , INF);

	inline double ABS(double x)			{return x < 0. ? -x : x;}

	inline double MIN(double x,double y){return x < y ? x : y;}
	inline double MAX(double x,double y){return x < y ? y : x;}

	inline bool EQU(double x,double y)	{return ABS(x-y) < EPS;}

	inline double cross_mul(const Vector & a,const Vector & b)
	{//叉乘积
		return a.x * b.y - a.y * b.x;
	}	

	inline double point_mul(const Vector & a,const Vector & b)
	{//点乘积
		return a.x * b.x + a.y * b.y;
	}

	inline bool split_by(const Point & a1,const Point & a2,const Point & b1,const Point & b2)
	{//点b1和b2在线段a1-a2两侧
		return ((b1 - a1) * (a2 - a1)) * ((b2 - a1) * (a2-a1)) < 0.;
	}

	inline bool cross(const Point & a1,const Point & a2,const Point & b1,const Point & b2)
	{//线段a1-a2和线段b1-b2是否相交（严格相交）
		return split_by(a1,a2,b1,b2) && split_by(b1,b2,a1,a2);
	}

	inline bool on(const Point & a1,const Point & a2,const Point & b)
	{//点b在线段a1-a2上（包括端点）
		return EQU( (b - a1) * (b - a2) , 0. ) && ( ((b - a1) ^ (b - a2)) <= 0. );
	}

	inline double rand_double()
	{
		return (double)rand() / (double)RAND_MAX;
	}

	struct cmp
	{
		int focus;
		cmp(int focus = 0);
		bool operator () (const Point & a,const Point & b);
	};
}

#endif //_YYY_METHODS_H_