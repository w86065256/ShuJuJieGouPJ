#include "submit-6MixQuery.h"
#include "universe.h"

void SetEnvironmentFromMixQuery() {

}

void AddPointFromMixQuery(int id, double x, double y) {
	AP;
}

void DeletePointFromMixQuery(int id) {
	DP;
}

std::vector<int> QueryPointFromMixQuery(double x, double y) {
    return QP;
}

void AddPolygonFromMixQuery(int id, int n, std::vector<std::pair<double, double>> &polygon) {
	AG;
}

void DeletePolygonFromMixQuery(int id) {
	DG;
}

std::vector<int> QueryPolygonFromMixQuery(int n, std::vector<std::pair<double, double>> &polygon) {
    return QG;
}

