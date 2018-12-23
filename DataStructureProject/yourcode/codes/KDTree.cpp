#include <algorithm>
#include <stdexcept>
#include <map>
#include <cstdlib>
#include "KDTree.h"
#include "methods.h"
#include "Poly_Point.h"

namespace yyy
{
	KDTNode::KDTNode
	(
		const Point & poi, 
		int dir ,
		const Box & box ,
		KDTNode * lef , 
		KDTNode * rig , 
		bool deled , 
		double alpha
	)
	{
		this->poi = poi;
		this->dir = dir;
		this->box = box;
		this->lef = lef;
		this->rig = rig;
		this->alpha = alpha;

		size = not deled;
		bad_size = deled;
		height = not deled;
		this->deled = deled;
	}	
	KDTNode::KDTNode	
	(
		int dir ,
		const Point & poi, 
		const Box & box ,
		KDTNode * lef , 
		KDTNode * rig , 
		bool deled ,
		double alpha
	)
	{
		this->poi = poi;
		this->dir = dir;
		this->box = box;
		this->lef = lef;
		this->rig = rig;
		this->alpha = alpha;

		size = not deled;
		bad_size = deled;
		height = not deled;
		this->deled = deled;
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

	bool KDTNode::bad()
	{
		int lim = all_size() * alpha;
		int lsiz = lef ? lef->all_size() : 0;
		int rsiz = rig ? rig->all_size() : 0;

		return lsiz > all_size() || rsiz > all_size();
	}

	void KDTNode::update()
	{
		size = !deled;
		bad_size = deled;
		height = 0;

		for(int k = 0;k < 2;k++)
		{
			if(!son(k))
				continue;
			size += son(k)->size;
			bad_size += son(k)->bad_size;
			height = std::max(height , son(k)->height);
		}

		height ++;
	}
	
	void KDTNode::del_self()
	{
		deled = true;
		update();
	}
	void KDTNode::del(const Point & tar)
	{
		lef = check(lef);
		rig = check(rig);

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
		lef = check(lef);
		rig = check(rig);

		int k = p[dir] >= poi[dir];

		if(!son(k))
			son(k) = new KDTNode(dir ^ 1 , p , box.cut(dir , k^1 , poi[dir]));
		else
			son(k)->add(p);

		update();
	}

	void ask_poly(KDTNode * d , const Polygon & poly , std::vector< Point> & res)
	{
		if(d == 0)
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

	static void spash_kdt(KDTNode * root , Point lis[] , int & tot)
	{
		if(!root)
			return ;
		if(!root->deled)
			lis[tot++] = root->poi;
		spash_kdt(root->lef , lis , tot);
		spash_kdt(root->rig , lis , tot);
	}

	KDTNode * rebuild(KDTNode * root)
	{
		KDTNode * res = 0;

		if(root == 0 || root->size == 0)
			return 0;
		int dir = root->dir;
		int size = root->size;
		Box now_box = root->box;
		Point * pois = new Point [root->size];

		int _tot = 0;

		spash_kdt(root , pois , _tot);

		delete root;

		res = make_kdt(pois , pois + size , dir , now_box);

		return res;
	}

	KDTNode * check(KDTNode * d)
	{
		if(d && d->bad())
			return rebuild(d);
		return d;
	}


	int KDTNode::all_size()
	{
		return size + bad_size;
	}
} 