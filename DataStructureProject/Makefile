.PHONY : ALL
ALL : main

need_os = \
./yourcode/submit-1AddPolygonBeforeQueryPoint.o \
./yourcode/submit-2AddPointBeforeQueryPolygon.o \
./yourcode/submit-3AddBeforeQuery.o \
./yourcode/submit-4MixQueryPoint.o \
./yourcode/submit-5MixQueryPolygon.o \
./yourcode/submit-6MixQuery.o \
./yourcode/codes/Box.o \
./yourcode/codes/Point.o \
./yourcode/codes/Polygon.o \
./yourcode/codes/methods.o \
./yourcode/universe.o \


main : main.o  $(need_os)
	g++ main.o $(need_os) -o main -std=c++11 -O2

