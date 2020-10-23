#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define INF 2000'000'000
using namespace std; 
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
template<typename T> using ordered_set = tree<T , null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int MXN = 100'005;
vector < pair<int,int>> adj[MXN];
int anc[MXN][17];
int mx[MXN][17];
int mn[MXN][17];
int dep[MXN];
void build_anc(int v, int p = 0, int e = 0, int d = 0){
	anc[v][0] = p;
	mx[v][0] = e;
	mn[v][0] = p == 0 ? INF : e;
	dep[v] = d;
	for(int i = 1; i < 17; i++){
		anc[v][i] = anc[anc[v][i-1]][i-1];
		mx[v][i] = max(mx[v][i-1], mx[anc[v][i-1]][i-1]);
		mn[v][i] = min(mn[v][i-1], mn[anc[v][i-1]][i-1]);
	}
	for(auto & u : adj[v]){
		if(u.first != p){
			build_anc(u.first, v, u.second, d+1);
		}
	}
}

tuple<int,int,int> kth_anc(int v, int k){
	int cur_mn = INF, cur_mx = 0;
	while(k){
		const int msb = __lg(k);
		cur_mn = min(cur_mn, mn[v][msb]), cur_mx = max(cur_mx, mx[v][msb]);
		v = anc[v][msb], k -= 1 << msb;
	}
	return {v,cur_mn, cur_mx};
}

pair<int,int> solve(int a, int b){
	if(dep[b] > dep[a])
		swap(a, b);
	// move a to same height as b
	auto t = kth_anc(a, dep[a] - dep[b]);
	a = get<0>(t);
	int cur_mn = get<1>(t), cur_mx = get<2>(t);
	if(a == b)
		return {cur_mn, cur_mx};
	for(int i = 16; i >= 0; i--){// move all to be children of anc
		if(anc[a][i] != anc[b][i]){
			cur_mn = min({cur_mn, mn[a][i], mn[b][i]});
			cur_mx = max({cur_mx, mx[a][i], mx[b][i]});
			a = anc[a][i], b = anc[b][i];
		}
	}
	cur_mn = min({cur_mn, mn[a][0], mn[b][0]});
	cur_mx = max({cur_mx, mx[a][0], mx[b][0]});
	return {cur_mn, cur_mx};
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);//freopen("out", "w", stdout);
	int n, m;
	cin >> n;
	for(int i = 1,u,v, w; i < n && cin >> u >> v >> w; i++){
		adj[u].push_back({v,w}), adj[v].push_back({u,w});
	}
	build_anc(1);
	cin >> m;
	for(int i = 1, u, v; i <= m; i++){
		cin >> u >> v;
		auto ans = solve(u,v);
		cout << ans.first << " " << ans.second << "\n";
	}
	return 0;
}
