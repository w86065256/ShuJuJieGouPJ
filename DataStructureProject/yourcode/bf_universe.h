#ifndef _YYY_BF_UNIVERSE_H_
#define _YYY_BF_UNIVERSE_H_

#include "codes/all.h"
#include <map>

using namespace yyy;

namespace bf
{
	void SetEnvironment();

	void AddPoint(int id, double x, double y);
	void DeletePoint(int id);
	std::vector<int> QueryPoint(double x, double y);

	void AddPolygon(int id, int n, std::vector < std::pair<double, double> > &polygon);
	void DeletePolygon(int id);
	std::vector<int> QueryPolygon(int n, std::vector < std::pair<double, double> > &polygon);
}

#define BF_AP bf::AddPoint(id,x,y)
#define BF_DP bf::DeletePoint(id)
#define BF_QP bf::QueryPoint(x,y)
#define BF_AG bf::AddPolygon(id,n,polygon)
#define BF_DG bf::DeletePolygon(id)
#define BF_QG bf::QueryPolygon(n,polygon)

#endif //_YYY_BF_UNIVERSE_H_
