#include <algorithm>
#include "KDTree.h"
#include "methods.h"

namespace yyy
{
	KDTNode::KDTNode(int dir,Box box,KDTNode * lef, KDTNode * rig)
	{
		this->dir = dir;
		this->box = box;
		this->lef = lef;
		this->rig = rig;

		size = 0;
		deled = false;
	}

	KDTNode::~KDTNode()
	{
		if(lef)
			delete lef;
		if(rig)
			delete rig;
	}

	KDTNode * KDTNode::son(int k)
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
	
	void KDTNode::del()
	{
		deled = true;
		update();
	}

	//左儿子总是更左、更上
	KDTNode * make_kdt(Point * l,Point * r,int dir,Box now_box)
	{
		if(l >= r)
			return 0;

		KDTNode * tar = new KDTNode(dir , now_box);

		std::sort(l , r , cmp(dir));
		Point * mid = l + ((r - l) >> 1);
		tar->p = *mid;

		//dir = 0 : cut rig([0][1]) , dir = 1 : cut bot([1][0])
		tar->lef = make_kdt(l , mid , dir ^ 1 , now_box.cut(dir , dir^1 , (*mid)[dir]));

		//dir = 0 : cut lef([0][0]) , dir = 1 : cut top([1][1])
		tar->rig = make_kdt(mid + 1 , r , dir ^ 1 , now_box.cut(dir , dir , (*mid)[dir]));

		tar->update();

		return tar;
	}
}