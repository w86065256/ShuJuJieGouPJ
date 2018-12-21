.PHONY : ALL
ALL : main

need_cpps = \
./yourcode/submit-1AddPolygonBeforeQueryPoint.cpp \
./yourcode/submit-2AddPointBeforeQueryPolygon.cpp \
./yourcode/submit-3AddBeforeQuery.cpp \
./yourcode/submit-4MixQueryPoint.cpp \
./yourcode/submit-5MixQueryPolygon.cpp \
./yourcode/submit-6MixQuery.cpp \
./yourcode/codes/Box.cpp \
./yourcode/codes/Point.cpp \
./yourcode/codes/Polygon.cpp \
./yourcode/codes/methods.cpp \
./yourcode/codes/KDTree.cpp \
./yourcode/codes/Poly_Point.cpp \
./yourcode/codes/use_rtree.cpp \
./yourcode/universe.cpp \
./yourcode/bf_universe.cpp \

need_hs = \
./yourcode/submit-1AddPolygonBeforeQueryPoint.h \
./yourcode/submit-2AddPointBeforeQueryPolygon.h \
./yourcode/submit-3AddBeforeQuery.h \
./yourcode/submit-4MixQueryPoint.h \
./yourcode/submit-5MixQueryPolygon.h \
./yourcode/submit-6MixQuery.h \
./yourcode/codes/Box.h \
./yourcode/codes/Point.h \
./yourcode/codes/Polygon.h \
./yourcode/codes/methods.h \
./yourcode/codes/KDTree.h \
./yourcode/codes/Poly_Point.h \
./yourcode/codes/use_rtree.h \
./yourcode/universe.h \
./yourcode/bf_universe.h \

main : main.cpp  $(need_hs) $(need_cpps)
	g++ main.cpp $(need_cpps) -o main -std=c++11 -O2

#clean:
#	rm $(need_os)
