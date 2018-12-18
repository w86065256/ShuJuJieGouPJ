/*
	策略：
		两棵R树，一棵对小多边形，一棵对大多边形
		小多边形：
			用矩形去覆盖多边形，对每个点筛出其可能在的矩形，然后暴力判断
			R树中每个叶子节点指出其是哪个多边形
		大多边形：
			每个线段搞一条矩形
			引一条射线，看其穿过哪些叶子矩形
			R树中每个叶子指出其属于哪个多边形。
*/

#ifndef _YYY_USE_RTREE_H_
#define _YYY_USE_RTREE_H_

#include <vector>
#include "cloned/RTree.h"
#include "Polygon.h"
#include "Point.h"

using namespace yyy;

typedef RTree<int , double , 2> Myrtree;

extern Myrtree tree1;
extern Myrtree tree2;

const int alpha = 20;

void ask_point_1(const Point & poi , std::vector<int> & vec);
void add_poly_1(const Polygon & poly);
void add_poly_2(const Polygon & poly);
void add_poly(const Polygon & poly);


#endif //_YYY_USE_RTREE_H_