#ifndef _YYY_UNIVERSE_H_
#define _YYY_UNIVERSE_H_

#include "codes/all.h"
#include <map>

using namespace yyy;

void SetEnvironment();

void AddPoint(int id, double x, double y);
void DeletePoint(int id);
std::vector<int> QueryPoint(double x, double y);

void AddPolygon(int id, int n, std::vector < std::pair<double, double> > &polygon);
void DeletePolygon(int id);
std::vector<int> QueryPolygon(int n, std::vector < std::pair<double, double> > &polygon);

#define AP AddPoint(id,x,y)
#define DP DeletePoint(id)
#define QP QueryPoint(x,y)
#define AG AddPolygon(id,n,polygon)
#define DG DeletePolygon(id)
#define QG QueryPolygon(n,polygon)

#endif //_YYY_UNIVERSE_H_
