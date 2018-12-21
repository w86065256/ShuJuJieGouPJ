#include "universe.h"
#include <map>
#include <algorithm>
#include <time.h>

static std::map< int , Point > points;
static KDTNode * root = 0;

static int QP_time = 0;
static int QG_time = 0;

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

std::vector<int> QueryPolygon(int n, std::vector<std::pair<double, double>> &polygon) 
{
	//int time_1 = clock();

	std::vector<int> res;

	std::vector<Point> res_poi;

	Polygon pol(polygon);

	ask_poly(root , pol , res_poi);

	for(int i = 0;i < res_poi.size();i++)
		res.push_back(res_poi[i].id);
	
	std::sort(res.begin() , res.end());

	//int time_2 = clock();
	//QG_time += time_2 - time_1;
	//fprintf(stderr,"now polygon_time = %d\n",QG_time);

	return res;
}

std::vector<int> QueryPoint(double x, double y) 
{
	//int time_1 = clock();

	std::vector<int> res;
	ask_point(Point(x,y) , res);
	std::sort(res.begin() , res.end());


	//int time_2 = clock();
	//QP_time += time_2 - time_1;

	//fprintf(stderr,"now point_time = %d\n",QP_time);

	return res;
}

void AddPolygon(int id, int n, std::vector<std::pair<double, double>> &polygon) 
{
	Polygon poly(polygon , id);
	add_poly(poly);
}

void DeletePolygon(int id) 
{
	del_poly(id);
}
