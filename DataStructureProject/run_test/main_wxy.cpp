#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <fstream>
#include <map>
using namespace std;
#define MP make_pair
typedef long long ll;
const int N=1E6+5;
const int M=N*20;
const int L=5E5;
struct data_Point{
	int x,y;
}Point[N];
struct data_Poly{
	int x1,y1,x2,y2,xmin,xmax,ymin,ymax;
	data_Poly(int xx1,int yy1,int xx2,int yy2) 
	{ 
		if (xx1>xx2) { swap(xx1,xx2); swap(yy1,yy2); }
		x1=xx1; x2=xx2; y1=yy1; y2=yy2; 
		xmin=min(x1,x2); xmax=max(x1,x2);
		ymin=min(y1,y2); ymax=max(y1,y2);
	}
};
vector <int> tr0[M];
vector <pair<int,int>> tr1[M],tr1_all[M];
vector <data_Poly> Poly[N];
int tot,to[M],lc[M],rc[M],root,ans_time[N],tot0,tot1;
bool o_Point[N],o_Poly[N];
vector <int> ans_G;
map <int,int> to_point,to_poly; 

bool check_out(int t,int k,int l,int r,int id,int id2)
{
    if (!k) 
	{
		int x;
		if (!t) x=Point[id].x; else x=Point[id].y;
		return l>x||r<x;
	} else 
	{
		if (!t) return Poly[id][id2].xmin>r||Poly[id][id2].xmax<l; else return Poly[id][id2].ymin>r||Poly[id][id2].ymax<l;
	}
}

bool check_in(int t,int k,int l,int r,int id,int id2)
{
    if (!k) return l==r; else 
	{
		if (!t) return Poly[id][id2].xmin<=l&&Poly[id][id2].xmax>=r; else return Poly[id][id2].ymin<=l&&Poly[id][id2].ymax>=r;
	}
}

void add(int t,int &p,int l,int r,int id,int id2,int k) // if k=0: Point else Poly; if t=0: x-axis else y-axis; 
{
    if (check_out(t,k,l,r,id,id2)) return;
    if (!p) p=++tot;
    if (!k) tr0[p].push_back(id);
    if (check_in(t,k,l,r,id,id2))
    {
    	if (k==1) tr1[p].push_back(MP(id,id2));
    	return;
    }
	int mid=(l+r)/2;
	add(t,lc[p],l,mid,id,id2,k); add(t,rc[p],mid+1,r,id,id2,k); 
}

ll cha(ll x1,ll y1,ll x2,ll y2)
{
	return (ll) x1*y2-x2*y1;
}

bool check_down(int x,int y,const data_Poly &A) // check Poly is below Point(x,y)
{
//	cerr<<x<<" "<<y<<" "<<A.x1<<" "<<A.x2<<" "<<A.y1<<" "<<A.y2<<endl;
	if (A.ymax<y) return 1;
	if (A.ymin>y) return 0;
	return cha(x-A.x1,y-A.y1,A.x2-A.x1,A.y2-A.y1)<0;
}

void get_point(int t,int p,int l,int r,int x,int y)
{
	if (!p||l>x||r<x) return;
	{
		vector <pair<int,int>> &tr=tr1[p];
		for (int i=0;i<tr.size();i++) if (!o_Poly[tr[i].first]&&check_down(x,y,Poly[tr[i].first][tr[i].second])) 
		{
			ans_G.push_back(tr[i].first);
			ans_time[tr[i].first]^=1;
		}
	}
	if (l==r) return;
	int mid=(l+r)/2;
	get_point(t,lc[p],l,mid,x,y); get_point(t,rc[p],mid+1,r,x,y);
}

void get_poly(int p,int l,int r,const data_Poly & A)
{
	if (!p||l>A.x2||r<A.x1) return;
	if (A.x1<=l&&A.x2>=r)
	{
		vector <int> &tr=tr0[p];
		for (int i=0;i<tr.size();i++) if (!o_Point[tr[i]]&&check_down(Point[tr[i]].x,Point[tr[i]].y,A)) 
		{
			ans_G.push_back(tr[i]);
			ans_time[tr[i]]^=1;
		}
		return;
	}
	int mid=(l+r)/2;
	get_poly(lc[p],l,mid,A); get_poly(rc[p],mid+1,r,A);
}

void SetEnvironmentFromMixQuery() {

}

int change(double x)
{
//	cerr<<x*100<<" "<<ceil(x*100)<<endl;
    return ceil(x*100);
}

void AddPointFromMixQuery(int id, double x, double y) {
	id=to_point[id]=++tot0;
    x=change(x); y=change(y);
    Point[id].x=x;  Point[id].y=y;
   // cerr<<x<<" "<<y<<endl;
    add(0,root,-L,L,id,0,0);
}

void DeletePointFromMixQuery(int id) {
	id=to_point[id];
	o_Point[id]=1;
}

std::vector<int> QueryPointFromMixQuery(double x, double y) {
//	cerr<<x<<" "<<y<<endl;
	x=change(x); y=change(y);
//	cerr<<x<<" "<<y<<endl;
	get_point(0,root,-L,L,x,y);
	vector <int> ans;
	int u;
	for (int i=0;i<ans_G.size();i++) if (ans_time[u=ans_G[i]])
	{
		ans.push_back(u); 
		ans_time[u]=0;
	}
//	cerr<<ans_G.size()<<endl;
	ans_G.clear();
    return ans;
}

void AddPolygonFromMixQuery(int id, int n, std::vector<std::pair<double, double>> &polygon) {
	id=to_poly[id]=++tot1;
	for (int i=0;i<n;i++) 
	{
		Poly[id].push_back(data_Poly(change(polygon[i].first),change(polygon[i].second),
		change(polygon[(i+1)%n].first),change(polygon[(i+1)%n].second)));
	//	cerr<<id<<" "<<i<<" "<<Poly[id][i].x1<<" "<<Poly[id][i].x2<<" "<<Poly[id][i].y1<<" "<<Poly[id][i].y2<<endl;
		add(0,root,-L,L,id,i,1);
	}
}

void DeletePolygonFromMixQuery(int id) {
	id=to_poly[id];
	o_Poly[id]=1;
}

std::vector<int> QueryPolygonFromMixQuery(int n, std::vector<std::pair<double, double>> &polygon) {
    for (int i=0;i<n;i++) 
	{
		get_poly(root,-L,L,data_Poly(change(polygon[i].first),change(polygon[i].second),
		change(polygon[(i+1)%n].first),change(polygon[(i+1)%n].second)));
	//	cerr<<id<<" "<<i<<" "<<Poly[id][i].x1<<" "<<Poly[id][i].x2<<" "<<Poly[id][i].y1<<" "<<Poly[id][i].y2<<endl;
	}
	vector <int> ans;
	int u;
	for (int i=0;i<ans_G.size();i++) if (ans_time[u=ans_G[i]])
	{
		ans.push_back(u); 
		ans_time[u]=0;
	}
	ans_G.clear();
    return ans;
}


int environment_variable(0);

void PrintAnswerOut(std::fstream &fout, std::vector<int> &answer_vector)
{
    for (auto answer : answer_vector) {
        fout << answer << " ";
    }
    fout << std::endl;
}

void AddPoint(std::fstream &fin) {
    int id;
    double x;
    double y;
    fin >> id;
    fin >> x >> y;

    switch (environment_variable) {
        case 6: {
            AddPointFromMixQuery(id, x, y);
            break;
        }
        default:
            std::cout << "Good morning, and in case I don't see ya, good afternoon, good evening, and good night!" << std::endl;
    }
}

void DeletePoint(std::fstream &fin) {
    int id;
    fin >> id;
    switch (environment_variable) {
        case 6: {
            DeletePointFromMixQuery(id);
            break;
        }
        default: {
            std::cout << "Don't cry because it's over, smile because it happened." << std::endl;
        }
    }
}

void QueryPoint(std::fstream &fin, std::fstream &fout) {
    double x;
    double y;
    fin >> x >> y;
    std::vector<int> query_answer;
    switch (environment_variable) {
        case 6: {
            query_answer = QueryPointFromMixQuery(x, y);
            break;
        }
        default: {
            std::cout << "You can't connect the dots looking forward; you can only connect them looking backwards." << std::endl;
        }
    }
    PrintAnswerOut(fout, query_answer);
}

void AddPolygon(std::fstream &fin) {
    int id;
    int n;
    std::vector< std::pair<double, double> > polygon;
    fin >> id;
    fin >> n;
    double x;
    double y;
    for (int i = 0; i < n; ++i) {
        fin >> x >> y;
        polygon.emplace_back(std::make_pair(x, y));
    }

    switch (environment_variable) {
        case 6: {
            AddPolygonFromMixQuery(id, n, polygon);
            break;
        }
        default: {
            std::cout << "We slept on floors. We waded across rivers." << std::endl;
        }
    }
}

void DeletePolygon(std::fstream &fin) {
    int id;
    fin >> id;
    switch (environment_variable) {
        case 6: {
            DeletePolygonFromMixQuery(id);
            break;
        }
        default: {
            std::cout << "We accept the love we think we deserve." << std::endl;
        }
    }
}

void QueryPolygon(std::fstream &fin, std::fstream &fout) {
    int n;
    std::vector< std::pair<double, double> > polygon;
    fin >> n;
    double x;
    double y;
    for (int i = 0; i < n; ++i) {
        fin >> x >> y;
        polygon.emplace_back(std::make_pair(x, y));
    }
    std::vector<int> query_answer;
    switch (environment_variable) {
        case 6: {
            query_answer = QueryPolygonFromMixQuery(n, polygon);
            break;
        }
        default: {
            std::cout << "I'm not a hero, but I have served in a company full of them." << std::endl;
        }
    }
    PrintAnswerOut(fout, query_answer);
}

int main() {
   // std::cout << "Hello, World!" << std::endl;

    std::fstream fin("test.in", std::fstream::in);
    std::fstream fout("wxy.out", std::fstream::out);

    fin >> environment_variable;
	environment_variable=6;
    switch (environment_variable) {
        case 6: {
            SetEnvironmentFromMixQuery();
            break;
        }
        default:
            std::cout << "Who am I, where am I from, to where am I going" << std::endl;
    }

    int user_operation(0);
    while (fin >> user_operation) {
        switch (user_operation) {
            case 1: {
                // Add Point
                AddPoint(fin);
                break;
            }
            case 2: {
                // Delete Point
                DeletePoint(fin);
                break;
            }
            case 3: {
                // Query Point
                QueryPoint(fin, fout);
                break;
            }
            case 4: {
                // Add Polygon
                AddPolygon(fin);
                break;
            }
            case 5: {
                // Delete Polygon
                DeletePolygon(fin);
                break;
            }
            case 6: {
                // QueryPolygon
                QueryPolygon(fin, fout);
                break;
            }
            default: {
                // reach file ending
                std::cout << "! Hope is a good thing, maybe the best of things, and no good thing ever dies." << std::endl;
            }
        }
    }

    fin.close();
    fout.close();

  //  std::cout << "Well Done!" << std::endl;

    return 0;
}

