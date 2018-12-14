#include "submit-3AddBeforeQuery.h"
#include "universe.h"

void SetEnvironmentFromAddBeforeQuery() {

}

void AddPointFromAddBeforeQuery(int id, double x, double y) {
	AP;
}

void AddPolygonFromAddBeforeQuery(int id, int n, std::vector<std::pair<double, double> > &polygon) {
	AG;
}

std::vector<int> QueryPointFromAddBeforeQuery(double x, double y) {
    return QP;
}

std::vector<int> QueryPolygonFromAddBeforeQuery(int n, std::vector<std::pair<double, double> > &polygon) {
    return QG;
}
