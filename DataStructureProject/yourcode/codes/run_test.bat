echo off
g++ test.cpp Point.cpp Polygon.cpp Box.cpp methods.cpp KDTree.cpp Poly_Point.cpp use_rtree.cpp -o test -std=c++11
test
