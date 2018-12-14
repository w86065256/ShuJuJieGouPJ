#include "Polygon.h"
#include "Point.h"
#include "Box.h"
#include <iostream>
#include <map>
#include <time.h>
#include <stdlib.h>

using namespace yyy;


#define MAKE_S(_) const char * _test_s = _;int _test_cnt_ = 0
#define ASSERT(_) {_test_cnt_++;if(!(_)) throw std::pair<const char *,int>(_test_s , _test_cnt_);}

void test_Point();
void test_Polygon();
void test_insied_box();
void test_insied_poly();

int main()
{
	srand(time(0));

	try
	{
		test_Point();
		test_Polygon();
		test_insied_box();
		test_insied_poly();
	}
	catch (std::pair<const char * , int> s)
	{
		printf("%s in %d\n",s.first , s.second);
		return 1;
	}
	catch(std::exception& e)
	{
		printf("failed. : runtime error.\n");
		return 1;
	}

	printf("all test passed.\n");


	return 0;
}

void test_insied_poly()
{
	MAKE_S("test inside poly fail");
	
	{
		double xys[] = {0,0,32,30,0,50,-20,-20,};

		Polygon y;
		for(int i = 0;i < sizeof(xys) / sizeof(double);i += 2)
			y.push_back( Point(xys[i] , xys[i+1] ) );

		ASSERT( Point(0,10).inside(y) );
		ASSERT( Point(31,30).inside(y) );
		ASSERT( !Point(32,30).inside(y) );
	}


	{
		double xys[] = 
		{
			3.97 , 3.97 ,
			2.01 , 0.98 ,
			7.01 , 1.98 ,
			2.01 , 0.00 , 
			-2.99 , 0.00,
			-2.01 , 1.98,
		};

		Polygon y;
		for(int i = 0;i < sizeof(xys) / sizeof(double);i += 2)
			y.push_back( Point(xys[i] , xys[i+1] ) );

		ASSERT( Point(2.37 , 2.14).inside(y) );
		ASSERT( Point(4.82 , 1.29).inside(y) );
		ASSERT( Point(1.83 , 0.75).inside(y) );
		ASSERT( Point(-1.42 , 0.70).inside(y) );

		ASSERT( !Point(1.08 , 3.84).inside(y) );
		ASSERT( !Point(0.37 , 2.78).inside(y) );
		ASSERT( !Point(0.00 , 0.00).inside(y) );
		ASSERT( !Point(-1.26 , -0.67).inside(y) );
	}
}

void test_insied_box()
{
	MAKE_S("test box failed");

	Box box(50,-20,0,100);

	ASSERT( Point(30,30).inside(box) );
	ASSERT( Point(-3,7).inside(box) );
	ASSERT( !Point(-30,7).inside(box) );
	ASSERT( !Point(-300,700).inside(box) );

	Polygon y;
	y.push_back( Point(30,20) );
	y.push_back( Point(30,10) );
	y.push_back( Point(-14,3) );
	y.push_back( Point(80,30) );

	ASSERT( y.inside(box) );

	y.push_back( Point(-30,10) );

	ASSERT( !y.inside(box) );

}

void test_Point()
{
	MAKE_S("test Point failed");

	Point a(1,2);
	Point b(2,3);

	ASSERT(a != b);

	a += Point(1,1);

	ASSERT(a == b);

	b = a * 2;

	ASSERT(b == Point(4,6));

	ASSERT(Point(3,4) < Point(3,5));
	ASSERT(Point(3,4) > Point(3,3));
	ASSERT(Point(3,4) <= Point(3,5));
	ASSERT(Point(3,4) <= Point(3,4));
	ASSERT(Point(3,4) != Point(3,5));
}

void test_Polygon()
{
	MAKE_S("test Polygon failed");

	Point a(1,2);
	Point b(2,3);
	Point c(3,4);
	Polygon d;

	d.push_back(a);
	d.push_back(b);
	d.push_back(c);

	ASSERT(d[0] == a);
	ASSERT(d[-1] == c);
	ASSERT(d[-2] == d[1]);
}