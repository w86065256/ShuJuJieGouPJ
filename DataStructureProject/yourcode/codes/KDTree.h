#ifndef _YYY_KDTREE_H_
#define _YYY_KDTREE_H_

#include "Point.h"
#include "Polygon.h"
#include "Box.h"
#include "methods.h"

namespace yyy
{
	struct KDTNode
	{
		int dir;	//方向。0表示x关心（纵向边），1表示y关心（横向边）
		Box box;
		KDTNode * lef;
		KDTNode * rig;
		Point p = Point(0,0);
		bool deled;

		int size;

		KDTNode(int dir = 0,Box box = Box(0,0,0,0) , KDTNode * lef = 0 , KDTNode * rig = 0);
		virtual ~KDTNode();

		KDTNode * son(int k);
		void update();
		void del();
	};

	KDTNode * make_kdt(Point * l,Point * r,int dir = 0,Box now_box = MAX_BOX);
}

#endif //_YYY_KDTREE_H_