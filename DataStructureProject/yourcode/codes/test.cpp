#include <iostream>
#include <map>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "Polygon.h"
#include "Point.h"
#include "Box.h"
#include "KDTree.h"
#include "Poly_Point.h"
#include "use_rtree.h"

using namespace yyy;


#define MAKE_S(_) const char * _test_s = _;int _test_cnt_ = 0
#define ASSERT(_) {_test_cnt_++;if(!(_)) throw std::pair<const char *,int>(_test_s , _test_cnt_);}

template <typename T>
bool ask_inside(const std::vector<T> & v , const T & a);
bool ask_inside(const std::vector<Point> & v , int id);
template <typename T>
bool vector_equ(const std::vector<T> & a1 , const std::vector<T> & a2);

template <>
bool ask_inside(const std::vector<Point> & v , const Point & a)
{
	for(int i = 0;i < v.size();i++)
	{
		if(v[i].is_same(a))
			return true;
	}
	return false;
}

void test_Point();
void test_Polygon();
void test_box();
void test_insied_box();
void test_insied_poly();
void test_kdt_node_make();
void test_polygon_cross_box();
void test_ask_poly();
void test_ask_poly_point();
void test_add_poly_point();
void test_add_rtree();
void test_ask_point_1();
void test_ask_point_2();
void test_kdt_rebuild();

int main()
{
	srand(time(0));

	try
	{
		test_Point();
		test_Polygon();
		test_box();
		test_insied_box();
		test_insied_poly();
		test_polygon_cross_box();
		test_ask_poly();
		test_ask_poly_point();
		test_add_poly_point();
		test_add_rtree();
		test_ask_point_1();
		test_ask_point_2();
		test_kdt_rebuild();
		test_kdt_node_make();
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

void test_kdt_rebuild()
{
	MAKE_S("test_kdt_rebuild failed");

	std::vector<Point> ps = 
	{
		Point(1,2),
		Point(2,3),
		Point(4,5),
		Point(6,7),
		Point(8,9),
	};

	auto root = new KDTNode();

	root->add_poly(ps);

	ASSERT(root -> size == 6);
	root->del(ps[0]);
	ASSERT(root -> size == 5);

	root = rebuild(root);
	ASSERT(root -> size == 5);

}

void test_ask_point_2()
{
	MAKE_S("test_ask_point_2 failed");
	{
		std::vector< Point > pois_1 = 
		{
			Point(-1,-1),
			Point(-3,2),
			Point(-2,3),
			Point(0,3),
			Point(-1,1),
			Point(2,1),
		};
		Polygon poly_1(pois_1 , 1);
		add_poly(poly_1 , 0);
	}

	{
		std::vector< Point > pois_2 = 
		{
			Point(-1,-1),
			Point(-3,0),
			Point(-1,4),
			Point(0,4),
			Point(1,2),
			Point(2,3),
			Point(3,2),
			Point(2,0),
		};
		Polygon poly_2(pois_2 , 2);
		add_poly(poly_2 , 0);
	}

	{
		std::vector< Point > pois_3 = 
		{
			Point(-1,0),
			Point(1,4),
			Point(2,2),
		};
		Polygon poly_3(pois_3 , 3);
		add_poly(poly_3 , 0);
	}

	{
		std::vector< Point > pois = 
		{
			Point(233,445),
			Point(768,987),
			Point(123,677),
		};
		Polygon poly(pois , 4);
		add_poly(poly , 0);
	}	
	{
		std::vector< Point > pois = 
		{
			Point(11122,4345),
			Point(76328,6545),
			Point(1223,6766),
		};
		Polygon poly(pois , 5);
		add_poly(poly , 0);
	}	
	{
		std::vector< Point > pois = 
		{
			Point(879,879),
			Point(345,4567),
			Point(323,3425),
		};
		Polygon poly(pois , 6);
		add_poly(poly , 0);
	}	
	{
		std::vector< Point > pois = 
		{
			Point(1879,546879),
			Point(23345,454567),
			Point(432323,63425),
		};
		Polygon poly(pois , 6);
		add_poly(poly , 0);
	}

	Point ps[8] = 
	{
		Point(-2,1),
		Point(0,1),
		Point(-1,-1),
		Point(2,2),
		Point(-1,2),
		Point(1,3),
		Point(-1,0),
		Point(-2.5 , 2),
	};

	{
		std::vector<int> vecs[8];

		ask_point(ps[0] , vecs[0]);
		ask_point(ps[1] , vecs[1]);
		ask_point(ps[2] , vecs[2]);
		ask_point(ps[3] , vecs[3]);
		ask_point(ps[4] , vecs[4]);
		ask_point(ps[5] , vecs[5]);
		ask_point(ps[6] , vecs[6]);
		ask_point(ps[7] , vecs[7]);

		ASSERT( vector_equ(vecs[0] , std::vector<int>({1,2,}) ) );

		ASSERT( vector_equ(vecs[1] , std::vector<int>({2,3,}) ) );
		ASSERT( vector_equ(vecs[2] , std::vector<int>({}) ) );
		ASSERT( vector_equ(vecs[3] , std::vector<int>({2,}) ) );
		ASSERT( vector_equ(vecs[4] , std::vector<int>({1,2,}) ) );
		ASSERT( vector_equ(vecs[5] , std::vector<int>({3,}) ) );
		ASSERT( vector_equ(vecs[6] , std::vector<int>({1,2,}) ) );
		ASSERT( vector_equ(vecs[7] , std::vector<int>({1,}) ) );
	}

	del_poly(1 , 0);

	{
		std::vector<int> vecs[8];

		ask_point(ps[0] , vecs[0]);
		ask_point(ps[1] , vecs[1]);
		ask_point(ps[2] , vecs[2]);
		ask_point(ps[3] , vecs[3]);
		ask_point(ps[4] , vecs[4]);
		ask_point(ps[5] , vecs[5]);
		ask_point(ps[6] , vecs[6]);
		ask_point(ps[7] , vecs[7]);

		ASSERT( vector_equ(vecs[0] , std::vector<int>({2,}) ) );

		ASSERT( vector_equ(vecs[1] , std::vector<int>({2,3,}) ) );
		ASSERT( vector_equ(vecs[2] , std::vector<int>({}) ) );
		ASSERT( vector_equ(vecs[3] , std::vector<int>({2,}) ) );
		ASSERT( vector_equ(vecs[4] , std::vector<int>({2,}) ) );
		ASSERT( vector_equ(vecs[5] , std::vector<int>({3,}) ) );
		ASSERT( vector_equ(vecs[6] , std::vector<int>({2,}) ) );
		ASSERT( vector_equ(vecs[7] , std::vector<int>({}) ) );
	}


	tree1.RemoveAll();
	tree2.RemoveAll();
}

void test_ask_point_1()
{
	MAKE_S("test_ask_point_1 failed");
	{
		std::vector< Point > pois_1 = 
		{
			Point(-1,-1),
			Point(-3,2),
			Point(-2,3),
			Point(0,3),
			Point(-1,1),
			Point(2,1),
		};
		Polygon poly_1(pois_1 , 1);
		add_poly(poly_1);
	}

	{
		std::vector< Point > pois_2 = 
		{
			Point(-1,-1),
			Point(-3,0),
			Point(-1,4),
			Point(0,4),
			Point(1,2),
			Point(2,3),
			Point(3,2),
			Point(2,0),
		};
		Polygon poly_2(pois_2 , 2);
		add_poly(poly_2);
	}

	{
		std::vector< Point > pois_3 = 
		{
			Point(-1,0),
			Point(1,4),
			Point(2,2),
		};
		Polygon poly_3(pois_3 , 3);
		add_poly(poly_3);
	}

	{
		std::vector< Point > pois = 
		{
			Point(233,445),
			Point(768,987),
			Point(123,677),
		};
		Polygon poly(pois , 4);
		add_poly(poly);
	}	
	{
		std::vector< Point > pois = 
		{
			Point(11122,4345),
			Point(76328,6545),
			Point(1223,6766),
		};
		Polygon poly(pois , 5);
		add_poly(poly);
	}	
	{
		std::vector< Point > pois = 
		{
			Point(879,879),
			Point(345,4567),
			Point(323,3425),
		};
		Polygon poly(pois , 6);
		add_poly(poly);
	}	
	{
		std::vector< Point > pois = 
		{
			Point(1879,546879),
			Point(23345,454567),
			Point(432323,63425),
		};
		Polygon poly(pois , 6);
		add_poly(poly);
	}

	Point ps[8] = 
	{
		Point(-2,1),
		Point(0,1),
		Point(-1,-1),
		Point(2,2),
		Point(-1,2),
		Point(1,3),
		Point(-1,0),
		Point(-2.5 , 2),
	};

	{
		std::vector<int> vecs[8];

		ask_point_1(ps[0] , vecs[0]);
		ask_point_1(ps[1] , vecs[1]);
		ask_point_1(ps[2] , vecs[2]);
		ask_point_1(ps[3] , vecs[3]);
		ask_point_1(ps[4] , vecs[4]);
		ask_point_1(ps[5] , vecs[5]);
		ask_point_1(ps[6] , vecs[6]);
		ask_point_1(ps[7] , vecs[7]);

		ASSERT( vector_equ(vecs[0] , std::vector<int>({1,2,}) ) );

		ASSERT( vector_equ(vecs[1] , std::vector<int>({2,3,}) ) );
		ASSERT( vector_equ(vecs[2] , std::vector<int>({}) ) );
		ASSERT( vector_equ(vecs[3] , std::vector<int>({2,}) ) );
		ASSERT( vector_equ(vecs[4] , std::vector<int>({1,2,}) ) );
		ASSERT( vector_equ(vecs[5] , std::vector<int>({3,}) ) );
		ASSERT( vector_equ(vecs[6] , std::vector<int>({1,2,}) ) );
		ASSERT( vector_equ(vecs[7] , std::vector<int>({1,}) ) );
	}

	del_poly(2);

	{
		std::vector<int> vecs[8];

		ask_point_1(ps[0] , vecs[0]);
		ask_point_1(ps[1] , vecs[1]);
		ask_point_1(ps[2] , vecs[2]);
		ask_point_1(ps[3] , vecs[3]);
		ask_point_1(ps[4] , vecs[4]);
		ask_point_1(ps[5] , vecs[5]);
		ask_point_1(ps[6] , vecs[6]);
		ask_point_1(ps[7] , vecs[7]);

		ASSERT( vector_equ(vecs[0] , std::vector<int>({1,}) ) );

		ASSERT( vector_equ(vecs[1] , std::vector<int>({3,}) ) );
		ASSERT( vector_equ(vecs[2] , std::vector<int>({}) ) );
		ASSERT( vector_equ(vecs[3] , std::vector<int>({}) ) );
		ASSERT( vector_equ(vecs[4] , std::vector<int>({1,}) ) );
		ASSERT( vector_equ(vecs[5] , std::vector<int>({3,}) ) );
		ASSERT( vector_equ(vecs[6] , std::vector<int>({1,}) ) );
		ASSERT( vector_equ(vecs[7] , std::vector<int>({1,}) ) );
	}

	tree1.RemoveAll();
	tree2.RemoveAll();
}

template <typename T>
bool vector_equ(const std::vector<T> & a1 , const std::vector<T> & a2)
{
	if(a1.size() != a2.size())
		return false;
	for(int i = 0;i < a1.size();i++)
	{
		if(!ask_inside(a2 , a1[i]))
			return false;
	}
	return true;
}
void test_add_rtree()
{
	MAKE_S("test_add_rtree failed");

	std::vector<Point> poly_point = 
	{
		Point(0,0),
		Point(3,1),
		Point(2,2),
		Point(4,3),
		Point(2,4),
		Point(-1,4),
		Point(-2,3),
	};

	Polygon poly(poly_point);

	add_poly(poly);

	tree1.RemoveAll();
	tree2.RemoveAll();
}

void test_add_poly_point()
{
	MAKE_S("test add poly point failed");

	std::vector<Point> ps = 
	{
		Point(1,2),
		Point(2,3),
		Point(4,5),
		Point(6,7),
		Point(8,9),
	};

	auto root = new KDTNode();

	root->add_poly(ps);

	ASSERT(root -> size == 6);
	root->del(ps[0]);
	ASSERT(root -> size == 5);

}

void test_ask_poly_point()
{
	MAKE_S("test_ask_poly_point fail");

	Poly_Point ps[4] = 
	{
		Poly_Point(1,2,1 , 0),
		Poly_Point(2,3,2 , 1),
		Poly_Point(-1,3,3 , 2),
		Poly_Point(-2,1,4 , 3),
	};

	Poly_Point pss[4] = 
	{
		Poly_Point(1,2,1 , 0),
		Poly_Point(2,3,2 , 1),
		Poly_Point(-1,3,3 , 2),
		Poly_Point(-2,1,4 , 3),
	};

	std::vector<Point> poly_point = 
	{
		Point(0,0),
		Point(3,1),
		Point(2,2),
		Point(4,3),
		Point(2,4),
		Point(-1,4),
		Point(-2,3),
	};

	Polygon poly (poly_point);

	ASSERT(ps[0].inside(poly));
	ASSERT(ps[1].inside(poly));
	ASSERT(ps[2].inside(poly));
	ASSERT(!ps[3].inside(poly));

	KDTNode * root = make_kdt(pss , pss + 4);

	std::vector<Point> res;
	ask_poly(root , poly , res);

	ASSERT(res.size() == 3);

	ASSERT(  ask_inside<Point>( res , ps[0] ) );
	ASSERT(  ask_inside<Point>( res , ps[1] ) );
	ASSERT(  ask_inside<Point>( res , ps[2] ) );
	ASSERT( !ask_inside<Point>( res , ps[3] ) );

	delete root;
}

template <typename T>
bool ask_inside(const std::vector<T> & v , const T & a)
{
	for(int i = 0;i < v.size();i++)
	{
		if(v[i] == a)
			return true;
	}
	return false;
}

bool ask_inside(const std::vector<Point> & v , int id)
{
	for(int i = 0;i < v.size();i++)
	{
		if(v[i].id == id)
			return true;
	}
	return false;
}

void test_ask_poly()
{
	MAKE_S("test_ask_poly fail");

	Point ps[4] = 
	{
		Point(1,2,1),
		Point(2,3,2),
		Point(-1,3,3),
		Point(-2,1,4),
	};
	Point pss[4] = 
	{
		Point(1,2,1),
		Point(2,3,2),
		Point(-1,3,3),
		Point(-2,1,4),
	};

	std::vector<Point> poly_point = 
	{
		Point(0,0),
		Point(3,1),
		Point(2,2),
		Point(4,3),
		Point(2,4),
		Point(-1,4),
		Point(-2,3),
	};

	Polygon poly (poly_point);

	ASSERT(ps[0].inside(poly));
	ASSERT(ps[1].inside(poly));
	ASSERT(ps[2].inside(poly));
	ASSERT(!ps[3].inside(poly));

	KDTNode * root = make_kdt(pss , pss + 4);

	std::vector<Point> res;
	ask_poly(root , poly , res);

	ASSERT(res.size() == 3);
	ASSERT( ask_inside( res , ps[0] ) );
	ASSERT( ask_inside( res , ps[1] ) );
	ASSERT( ask_inside( res , ps[2] ) );
	ASSERT( !ask_inside( res , ps[3] ) );

	Point p1(0,0,12);
	root->add(p1);
	auto y = ask_poly(root , poly);

	ASSERT(y.size() == 3);
	ASSERT( ask_inside( y , ps[0] ) );
	ASSERT( ask_inside( y , ps[1] ) );
	ASSERT( ask_inside( y , ps[2] ) );
	ASSERT( !ask_inside( y , ps[3] ) );
	ASSERT( !ask_inside( y , p1 ) );

	root->del(ps[0]);
	y = ask_poly(root , poly);

	ASSERT(y.size() == 2);
	ASSERT( ask_inside( y , ps[1] ) );
	ASSERT( ask_inside( y , ps[2] ) );
	ASSERT( !ask_inside( y , ps[3] ) );
	ASSERT( !ask_inside( y , p1 ) );

	delete root;
}

void test_polygon_cross_box()
{
	MAKE_S("test_polygon_cross_box fail");

	Point p1(1,0);
	Point p2(1.5,2);
	Point p3(0,1);

	Polygon pol;
	pol.push_back(p1);
	pol.push_back(p2);
	pol.push_back(p3);

	Box box1(4,-1,0,.5);
	Box box2(5,3,2,5);

	ASSERT(pol.cross(box1));
	ASSERT(! pol.cross(box2));
}

void test_kdt_node_make()
{
	MAKE_S("test_kdt_node_make fail");

	{
		Point ps[8] = {
			Point(3,5),
			Point(6,3),
			Point(2,1),
			Point(6,1),
			Point(1,5),
			Point(1,7),
			Point(5,2),
			Point(4,3),
		};
		KDTNode * root = 0;
		root = make_kdt(ps , ps + 8 , 0);
		//printf("%f\n",(float)(root->box.top));
		ASSERT(root->box == MAX_BOX);
		ASSERT(root->size == 8);
		ASSERT(root->poi == Point(4,3));
		ASSERT(root->lef->box.top == root->box.top);
		ASSERT(root->lef->box.lef == root->box.lef);
		ASSERT(root->lef->box.rig != root->box.rig);
		ASSERT(root->rig->box.bot == root->box.bot);
		ASSERT(root->rig->box.rig == root->box.rig);
		ASSERT(root->rig->box.lef != root->box.lef);
		delete root;
	}

	{
		KDTNode * u = new KDTNode();
		KDTNode * y = new KDTNode();

		y->son(0) = u;
		ASSERT(y->lef == u);
		ASSERT(y->rig == 0);
		delete y;
	}

	{
		Point ps[8] = {
			Point(3,5),
			Point(6,3 , 9),
			Point(2,1 , 6),
			Point(6,1 , 12),
			Point(1,5),
			Point(1,7),
			Point(5,2),
			Point(4,3),
		};

		KDTNode * root = new KDTNode(0,ps[0],MAX_BOX);
		for(int i = 1;i <= 7;i++)
			root->add(ps[i]);

		ASSERT(root->box == MAX_BOX);
		ASSERT(root->size == 8);
		ASSERT(root->poi == Point(3,5));
		ASSERT(root->lef->box.top == root->box.top);
		ASSERT(root->lef->box.lef == root->box.lef);
		ASSERT(root->lef->box.rig != root->box.rig);
		ASSERT(root->rig->box.bot == root->box.bot);
		ASSERT(root->rig->box.rig == root->box.rig);
		ASSERT(root->rig->box.lef != root->box.lef);

		root->del(ps[1]);
		ASSERT(root->size == 7)

		root->del(ps[2]);
		ASSERT(root->size == 6)

		delete root;
	}

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
	{
		double xys[] = 
		{
			2,3,
			3,1,
			-4,-2,
			-1,3,
		};

		Polygon y;
		for(int i = 0;i < sizeof(xys) / sizeof(double);i += 2)
			y.push_back( Point(xys[i] , xys[i+1] ) );

		ASSERT( Point(2,1).inside(y) );
		ASSERT( Point(-1,1).inside(y) );

		ASSERT( !Point(1,3).inside(y) );
		ASSERT( !Point(3,-2).inside(y) );
		ASSERT( !Point(-4,2).inside(y) );
		ASSERT( !Point(2,3).inside(y) );

	}
}

void test_box()
{
	MAKE_S("test box failed");

	Box b(-1,3,5,6);

	ASSERT(b.top == -1);
	ASSERT(b.lef == 3);
	ASSERT(b.bot == 5);
	ASSERT(b.rig == 6);

	ASSERT(b == Box(-1,3,5,6));

	b = Box(1,2,3,4);	

	ASSERT(b == Box(1,2,3,4));
	ASSERT(b[0][0] == b.lef);
	ASSERT(b[0][1] == b.rig);
	ASSERT(b[1][0] == b.bot);
	ASSERT(b[1][1] == b.top);
}

void test_insied_box()
{
	MAKE_S("test inside box failed");

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

	auto r = Point( std::pair<double,double>(12,4) );
	ASSERT(r + Point(3,5) == Point( std::pair<double,double>(15,9) ) );
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

	{
		std::vector<Point> v = {a,b,c,};
		auto y = Polygon(v);

		ASSERT(y[0] == a);
		ASSERT(y[1] == b);
		ASSERT(y[-1] == c);
	}


	{
		std::pair<double,double> pa(a.x,a.y);
		std::pair<double,double> pb(b.x,b.y);
		std::pair<double,double> pc(c.x,c.y);
		std::vector<Point> v = {pa,pb,pc,};
		auto y = Polygon(v);

		ASSERT(y[0] == a);
		ASSERT(y[1] == b);
		ASSERT(y[-1] == c);
	}
}