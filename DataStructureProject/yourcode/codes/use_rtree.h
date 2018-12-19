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
	
	因为这不是个概念，而是个全局策略，所以就不封装了。
*/

#ifndef _YYY_USE_RTREE_H_
#define _YYY_USE_RTREE_H_

#include <vector>
#include <map>
#include <set>
#include "cloned/RTree.h"
#include "Polygon.h"
#include "Point.h"
#include "methods.h"

using namespace yyy;

typedef std::pair<int ,int> Pii;

extern RTree< int , double , 2> tree1;
extern RTree< Pii , double , 2> tree2;

//extern std::map<int , Polygon> polys_2; //从 id 到 Polygon 的映射 ，只对大多边形有效，故是O(n)的
extern std::map<int , Polygon> polys; //从 id 到 Polygon 的映射

const int alpha = 20;
const int test_time = 3;

void ask_point_1(const Point & poi , std::vector<int> & vec);
void ask_point_2(const Point & poi , std::vector<int> & vec);
void add_poly_1(const Polygon & poly);
void add_poly_2(const Polygon & poly);
void add_poly(const Polygon & poly , int alp = -1);
void ask_point(const Point & poi , std::vector<int> & vec);
void del_poly_1(const Polygon & poly);
void del_poly_2(const Polygon & poly);
void del_poly(int id , int alp = -1);

struct Callback_1
{
	std::vector<int> & ids;
	Point poi;
	Callback_1(std::vector<int> & vec , Point p):ids(vec) , poi(p)
	{}
	bool operator () (int id)
	{
		const Polygon & poly = polys[id];
		if(poi.inside(poly))
			ids.push_back(poly.id);
		return true;
	}
};

struct Callback_2
{
	std::set<int> & bad;
	Point l1;
	Point l2;
	std::map<int , bool> & poly_cnt;
	Callback_2(std::map<int , bool> & map , Point a , Point b , std::set<int> & set)
		:poly_cnt(map),bad(set),l1(a),l2(b)
	{}
	bool operator () ( const Pii & a )
	{
		const Polygon & poly = polys[a.first];
		const Point & p1 = poly[a.second];
		const Point & p2 = poly[a.second + 1];
		
		if(on(p1,p2,l1))
		{
			bad.insert(a.first);
			return true;
		}

		if(cross(l1,l2,p1,p2))
		{
			poly_cnt[poly.id] ^= 1;
		}

		return true;
	}
};

#endif //_YYY_USE_RTREE_H_