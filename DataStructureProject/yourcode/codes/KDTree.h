#ifndef _YYY_KDTREE_H_
#define _YYY_KDTREE_H_

#include <vector>

#include "Point.h"
#include "Polygon.h"
#include "Box.h"
#include "methods.h"

namespace yyy
{
	struct KDTNode
	{
		double alpha;
		int dir;	//方向。0表示x关心（纵向边），1表示y关心（横向边）
		Box box;
		KDTNode * lef;
		KDTNode * rig;
		Point poi;
		bool deled;

		int size;
		int bad_size;
		int height;


		KDTNode
		(
			int dir = 0 ,
			const Point & poi = Point(0,0) ,
			const Box & box = MAX_BOX , 
			KDTNode * lef = 0 , 
			KDTNode * rig = 0 ,
			bool deled = false ,
			double alpha = DEFUALT_ALPHA
		);

		KDTNode
		(
			const Point & poi ,
			int dir = 0 ,
			const Box & box = MAX_BOX , 
			KDTNode * lef = 0 , 
			KDTNode * rig = 0 ,
			bool deled = false ,
			double alpha = DEFUALT_ALPHA
		);

		virtual ~KDTNode();
		
		int all_size();

		KDTNode * & son(int k);
		void update();
		void del_self();				//删掉自己
		void del(const Point & p);		//删掉子孙 ，要求编号相同
		void add(const Point & p);

		void add_poly(const Polygon & poly);

		bool bad();
	};

	KDTNode * make_kdt(Point * l,Point * r,int dir = 0,Box now_box = MAX_BOX);
	KDTNode * rebuild(KDTNode * root);

	//找到被poly包围的点
	void ask_poly(KDTNode * d , const Polygon & poly , std::vector< Point > & res);
	std::vector< Point > ask_poly(KDTNode * d , const Polygon & poly);

	KDTNode * check(KDTNode * d);
}

#endif //_YYY_KDTREE_H_