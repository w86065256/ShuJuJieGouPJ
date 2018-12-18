#include <algorithm>
#include <stdexcept>
#include "KDTree.h"
#include "methods.h"
#include "Poly_Point.h"

namespace yyy
{
	KDTNode::KDTNode(const Point & poi,int dir,const Box & box,KDTNode * lef, KDTNode * rig)
	{
		this->poi = poi;
		this->dir = dir;
		this->box = box;
		this->lef = lef;
		this->rig = rig;

		size = 1;
		deled = false;
	}	
	KDTNode::KDTNode(int dir,const Point & poi,const Box & box,KDTNode * lef, KDTNode * rig)
	{
		this->poi = poi;
		this->dir = dir;
		this->box = box;
		this->lef = lef;
		this->rig = rig;

		size = 1;
		deled = false;
	}

	KDTNode::~KDTNode()
	{
		if(lef)
			delete lef;
		if(rig)
			delete rig;
	}

	KDTNode * & KDTNode::son(int k)
	{
		if(k & 1)
			return rig;
		return lef;
	}

	void KDTNode::update()
	{
		size = !deled;
		size += get_size(lef);
		size += get_size(rig);
	}
	
	void KDTNode::del_self()
	{
		deled = true;
		update();
	}
	void KDTNode::del(const Point & tar)
	{
		if(tar.is_same(poi))
		{
			del_self();
			return ;
		}

		int k = tar[dir] > poi[dir];

		if(son(k) == 0)
			throw std::runtime_error("KDTNode::del : point not exsists");

		son(k) -> del(tar);
		update();
	}

	//左儿子总是更左、更上
	KDTNode * make_kdt(Point * l,Point * r,int dir,Box now_box)
	{
		if(l >= r)
			return 0;

		std::sort(l , r , cmp(dir));

		Point * mid = l + ((r - l) >> 1);
		KDTNode * tar = new KDTNode(dir , *mid , now_box);

		//dir = 0 : cut rig([0][1]) , dir = 1 : cut top([1][1])
		tar->lef = make_kdt(l , mid , dir ^ 1 , now_box.cut(dir , 1 , (*mid)[dir]));

		//dir = 0 : cut lef([0][0]) , dir = 1 : cut bot([1][0])
		tar->rig = make_kdt(mid + 1 , r , dir ^ 1 , now_box.cut(dir , 0 , (*mid)[dir]));

		tar->update();

		return tar;
	}

	void KDTNode::add(const Point & p)
	{
		int k = p[dir] >= poi[dir];

		if(!son(k))
		{
			Box new_box = box.cut(dir , k^1 , p[dir]);
			son(k) = new KDTNode(dir , p , new_box);
		}
		else
			son(k)->add(p);

		update();
	}

	void ask_poly(KDTNode * d , const Polygon & poly , std::vector< Point> & res)
	{
		if(d == 0)
			return;
		if(! poly.cross_or_inside(d->box) )
			return;
		if( (!d->deled) && d->poi.inside(poly))
			res.push_back(d->poi);
		ask_poly(d->son(0) , poly , res);
		ask_poly(d->son(1) , poly , res);
	}
	std::vector< Point > ask_poly(KDTNode * d , const Polygon & poly)
	{
		std::vector< Point > res;
		ask_poly(d , poly , res);
		return res;
	}

	void KDTNode::add_poly(const Polygon & poly)
	{
		for(int i = 0;i < poly.size();i++)
		{
			add( Poly_Point(poly[i] , poly.id , i) );
		}
	}
} 