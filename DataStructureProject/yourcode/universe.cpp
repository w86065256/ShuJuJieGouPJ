#include "universe.h"
#include <map>

static std::map< int , Point > points;
static KDTNode * root = 0;
static std::map< int , Polygon > polys;


void SetEnvironment() 
{}

void AddPoint(int id, double x, double y) 
{
	if(root == 0)
		root = new KDTNode( Point(x,y,id) );
	else root->add( Point(x,y,id) );

	points[id] = Point(x,y,id);
}

void DeletePoint(int id) 
{
	root->del( points[id] );
	points.erase(id);
}

std::vector<int> QueryPoint(double x, double y) 
{
	std::vector<int> res;
	Point p(x,y);
	for(auto & x : polys)
	{
		if(p.inside(x.second))
			res.push_back(x.first);
	}
	return res;
}

void AddPolygon(int id, int n, std::vector<std::pair<double, double>> &polygon) 
{
	polys[id] = Polygon(polygon , id);
}

void DeletePolygon(int id) 
{
	polys.erase(id);
}

std::vector<int> QueryPolygon(int n, std::vector<std::pair<double, double>> &polygon) 
{
	std::vector<int> res;

	std::vector<Point> res_poi;

	Polygon pol(polygon);

	ask_poly(root , pol , res_poi);

	for(int i = 0;i < res_poi.size();i++)
		res.push_back(res_poi[i].id);

	return res;
}