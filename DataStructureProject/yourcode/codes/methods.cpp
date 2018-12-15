#include "methods.h"
#include "Point.h"
#include "KDTree.h"

namespace yyy
{

	cmp::cmp(int focus)	
	{
		this->focus = focus;
	}

	bool cmp::operator () (const Point & a,const Point & b)
	{
		if(! EQU(a[focus] , b[focus]) )
			return a[focus] < b[focus];
		return a[focus ^ 1] < b[focus ^ 1];
	}

	int get_size(KDTNode * d)
	{
		if(d)
			return d->size;
		return 0;
	}
}