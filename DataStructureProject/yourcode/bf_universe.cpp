#include "universe.h"
#include <map>

namespace bf
{
	static std::map<int,Polygon> polys;
	static std::map<int,Point> points;
	
	void SetEnvironment() {
	}

	void AddPoint(int id, double x, double y) {
		points[id] = Point(x,y,id);
	}

	void DeletePoint(int id) {
		points.erase(id);
	}

	std::vector<int> QueryPoint(double x, double y) {
		std::vector<int> res;
		Point p(x,y);
		for(auto & x : polys)
		{
			if(p.inside(x.second))
				res.push_back(x.first);
		}
		return res;
	}

	Polygon * make_poly(int n, std::vector<std::pair<double, double>> &polygon , int id = 0)
	{//记得delete p
		Polygon * p = new Polygon(id);
		for(int i = 0;i < n;i++)
			p->v.push_back( Point(polygon[i].first , polygon[i].second) );
		return p;
	}

	void AddPolygon(int id, int n, std::vector<std::pair<double, double>> &polygon) {
		auto p = make_poly(n , polygon , id);
		polys[id] = *p;
		delete p;
	}

	void DeletePolygon(int id) {
		polys.erase(id);
	}

	std::vector<int> QueryPolygon(int n, std::vector<std::pair<double, double>> &polygon) {
		std::vector<int> res;
		
		Polygon * pp = make_poly(n,polygon);

		for(auto & x : points)
		{
			if(x.second.inside(*pp))
				res.push_back(x.first);
		}

		delete pp;

		return res;
	}
}