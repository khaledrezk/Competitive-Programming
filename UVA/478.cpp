#include<bits/stdc++.h>
#define INF 1000'000'000
#define F first
#define S second
using namespace std;
typedef  long long   ll;
typedef  unsigned long long ull;
typedef pair<double,double> pdd;

inline bool equal(double d1, double d2){
	return fabs(d1 - d2) <= 1e-6;
}

inline bool equal(pdd p1, pdd p2){
	return equal(p1.F,p2.F) && equal(p1.S, p2.S);
}

struct cirlce{
	pdd c;
	double r;
};

vector < vector < pdd > > polygons;
vector < int > p_indx, c_indx;
vector < cirlce > circles;

void input_polygons(){
	char c;
	for(int i = 1;cin >> c && c != '*'; i++){
		if(c == 'r'){
			vector < pdd > r(4);
			cin >> r[0].F >> r[0].S >> r[2].F >> r[2].S;
			r[1].F = r[0].F, r[1].S = r[2].S, r[3].F = r[2].F, r[3].S = r[0].S;
			polygons.push_back(r), p_indx.push_back(i);
		}
		else if(c == 't'){
			vector < pdd > t(3);
			for(auto &p : t)
				cin >> p.F >> p.S;
			polygons.push_back(t), p_indx.push_back(i);
		}
		else if(c == 'c'){
			cirlce ci;
			cin >> ci.c.F >> ci.c.S >> ci.r;
			circles.push_back(ci), c_indx.push_back(i);
		}
	}
}

inline double dist(pdd p1, pdd p2){
	return sqrt((p1.F - p2.F)*(p1.F-p2.F) + (p1.S - p2.S)* (p1.S - p2.S));
}

double signed_area(pdd a, pdd b, pdd c){
	/// af as 1
	/// bf bs 1
	/// cf cs 1
	/// af(bs-cs) - as(bf - cf) + (bf cs - bs cf)
	return a.F*(b.S - c.S) - a.S*(b.F - c.F) + (b.F * c.S - b.S * c.F);
}

bool inside_polygon(vector < pdd > poly, pdd point){
	int sz = poly.size(), cnt1=0, cnt_1 = 0;
	for(int ed = 0; ed < sz; ed++){
		pdd a = poly[ed], b = poly[(ed+1)%sz];
		double ar = signed_area(a,b,point);
		if(equal(ar, 0.0))// edges are not inside
			return false;
		ar > 0 ? cnt1++ : cnt_1++;
	}
	return (cnt1 == sz || cnt_1 == sz);
}

int main (){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("in", "r", stdin);
	//freopen("out", "w", stdout);
	input_polygons();
	pdd p, last (9999.9,9999.9);
	for(int tc = 1; cin >> p.F >> p.S && !equal(p, last); tc++){
		vector < int > ans;
		for(int i = 0; i < (int)circles.size(); i++){
			double d = dist(circles[i].c, p);
			if(!equal(d, circles[i].r) && d < circles[i].r)
				ans.push_back(c_indx[i]);
			
		}
		for(int i = 0; i < (int)polygons.size();i++){
			if(inside_polygon(polygons[i], p))
				ans.push_back(p_indx[i]);
		}
		sort(ans.begin(), ans.end());
		for(int & i : ans)
			cout << "Point " << tc << " is contained in figure " << i << endl;
		if(ans.empty()){
			cout << "Point " << tc << " is not contained in any figure" << endl;
		}
	}
	return 0;
}
