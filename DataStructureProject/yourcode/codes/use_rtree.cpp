#include "use_rtree.h"
#include "Box.h"
#include "methods.h"
#include <algorithm>

Myrtree tree1;
Myrtree tree2;

void add_poly1(const Polygon & poly)
{
	Box box(-INF , INF , INF , -INF);
	for(int i = 0;i < poly.size();i++)
	{
		box.bot = std::min(box.bot , poly[i].y);
		box.top = std::max(box.top , poly[i].y);
		box.lef = std::min(box.lef , poly[i].x);
		box.rig = std::max(box.rig , poly[i].x);
	}

	int min[2] = {box.lef , box.bot};
	int max[2] = {box.rig , box.top};
	tree1.add(min , max , poly.id);
}

void add_poly2(const Polygon & poly)
{}

void add_poly(const Polygon & poly)
{
	if(poly.size() <= alpha)
		add_poly_1();
	add_poly_2();
}

void ask_point()