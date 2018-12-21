#include "use_rtree.h"
#include "Box.h"
#include "methods.h"
#include <algorithm>

RTree< int , double , 2> tree1;
RTree< Pii , double , 2> tree2;
//RTree< int , double , 2> tree3;
std::map<int , Polygon> polys;
//std::map<int , points> points;

void add_poly_1(const Polygon & poly)
{
	const Box & box = poly.box;
	double min[2] = {box.lef , box.bot};
	double max[2] = {box.rig , box.top};
	tree1.Insert(min , max , poly.id);
}

void add_poly_2(const Polygon & poly)
{
	for(int i = 0;i < poly.size();i++)
	{
		double min[2] = {std::min(poly[i].x , poly[i+1].x) , std::min(poly[i].y , poly[i+1].y)};
		double max[2] = {std::max(poly[i].x , poly[i+1].x) , std::max(poly[i].y , poly[i+1].y)};
		tree2.Insert(min , max , Pii(poly.id , i) );
	}
}

void add_poly(const Polygon & poly , int alp)
{
	if(alp < 0)
		alp = alpha;
	if(poly.size() <= alp)
		add_poly_1(poly);
	else add_poly_2(poly);

	polys[poly.id] = poly;
}

void ask_point_1(const Point & poi , std::vector<int> & vec)
{
	double min[2] = {poi.x, poi.y,};
	double max[2] = {poi.x, poi.y,};

	Callback_1 cb(vec , poi);
	tree1.Search(min , max , cb);
}

void ask_point_2(const Point & poi , std::vector<int> & vec)
{
	std::map<int , int> yes;
	std::set<int> bad;

	for(int t = 1;t <= test_time;t++)
	{
		std::map<int , bool> cnt;
		Point l1 = poi;
		Point l2 = poi + Point(INF , (rand_double() - 1.) * 5.);

		Callback_2 cb2(cnt , l1 , l2 , bad);

		double min[2] = {std::min(l1.x , l2.x) , std::min(l1.y , l2.y)};
		double max[2] = {std::max(l1.x , l2.x) , std::max(l1.y , l2.y)};

		tree2.Search(min , max , cb2);

		for(const auto & x : cnt)
		{
			if(x.second)
			{
				yes[x.first] ++;
			}
		}
	}

	for(const auto & x : yes)
	{
		if(bad.find(x.first) != bad.end())
			continue;
		int get = x.second;
		if(get >= (test_time - get))
		{
			 vec.push_back(x.first);
		}
	}
}
void ask_point(const Point & poi , std::vector<int> & vec)
{
	ask_point_1(poi , vec);
	ask_point_2(poi , vec);
}

void del_poly_1(const Polygon & poly)
{
	const Box & box = poly.box;
	double min[2] = {box.lef , box.bot};
	double max[2] = {box.rig , box.top};
	tree1.Remove(min , max , poly.id);
}

void del_poly_2(const Polygon & poly)
{
	for(int i = 0;i < poly.size();i++)
	{
		double min[2] = {std::min(poly[i].x , poly[i+1].x) , std::min(poly[i].y , poly[i+1].y)};
		double max[2] = {std::max(poly[i].x , poly[i+1].x) , std::max(poly[i].y , poly[i+1].y)};
		tree2.Remove(min , max , Pii(poly.id , i) );
	}
}

void del_poly(int id , int alp)
{
	if(alp < 0)
		alp = alpha;

	const Polygon & poly = polys[id];

	if(poly.size() <= alp)
		del_poly_1(poly);
	else del_poly_2(poly);

	polys.erase(id);
}

/*
void add_point(const Point & poi)
{
	double min[2] = {poi.x , poi.y ,};
	double max[2] = {poi.x , poi.y ,};
	tree3.Insert(min , max , poi);
}

void del_point(int id)
{
	
}
void ask_poly(const Polygon & poly)
{
	
}
*/
