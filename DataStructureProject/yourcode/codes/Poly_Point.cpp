#include "Poly_Point.h"

namespace yyy
{
	Poly_Point::Poly_Point(double x,double y,int id,int k)
		:Point(x,y,id)
	{
		this->k = k;
	}	

	Poly_Point::Poly_Point(const Point & poi,int id,int k)
		:Point(poi.x , poi.y ,id)
	{
		this->k = k;
	}

	Poly_Point::Poly_Point(const Point & poi,int k)
		:Point(poi.x , poi.y ,poi.id)
	{
		this->k = k;
	}
}