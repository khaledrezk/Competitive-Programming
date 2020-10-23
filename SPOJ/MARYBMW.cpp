#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define INF 2000'000'000
using namespace std; 
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
template<typename T> using ordered_set = tree<T , null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct edge{
	int u, v;
	ll w;
	bool operator<(const edge & r) const{
		return w < r.w;
	}
};

struct dsu{
	vector < int > p, r;
	dsu(int n){
		p.resize(n), r.resize(n);
		for(int i = 1; i < n; i++){
			p[i] = i;
		}
	}
	int find(int x){
		return x == p[x] ? x : p[x] = find(p[x]);
	}
	bool union_set(edge & e){
		int x = find(e.u), y = find(e.v);
		if(x == y)
			return 0;
		if(r[x] > r[y])
			swap(x, y);
		if(r[x] == r[y])
			r[y]++;
		p[x] = y;
		return 1;
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);//freopen("out", "w", stdout);
	int t, n, m;
	cin >> t;
	while(t-- && cin >> n >> m){
		vector < edge > edges(m);
		for(auto & e: edges){
			cin >> e.u >> e.v >> e.w;
		}
		sort(edges.rbegin(), edges.rend());
		ll ans = -1;
		dsu ds(n+1);
		for(auto & e : edges){// e will be added with all connected pairs
			ds.union_set(e);
			if(ds.find(1) == ds.find(n)){
				ans = e.w;
				break;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
