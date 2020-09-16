#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
#define INF 3e9
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef tree<int, null_type,less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
constexpr int MXN = 1e5 + 5;
struct seg_tree{
	int cnt;
	seg_tree *left, *right;
	seg_tree(){
		cnt = 0, left = right = this;
	}
	seg_tree(int c, seg_tree* l, seg_tree* r){
		cnt = c, left = l, right = r;
	}
	
	seg_tree* insert(int val, ll tl = -INF, ll tr = INF){
		if(tl > val || tr < val)
			return this;
		else if(tl == tr){
			return new seg_tree(cnt + 1, left, right);
		}
		ll mid = tl + (tr - tl) / 2;
		auto l = left -> insert(val, tl, mid);
		auto r = right -> 	insert(val, mid+1, tr);
		return new seg_tree(l->cnt + r->cnt, l, r);
	}
};


ll w[MXN], dep[MXN], anc[MXN][18], n, m;
seg_tree* roots[MXN];

vector < int > adj[MXN];

void build(int v, int par = 0, int d = 1){
	anc[v][0] = par, dep[v] = d;
	for(int p = 1; p < 18; p++){
		anc[v][p] = anc[anc[v][p-1]][p-1];
	}
	roots[v] = roots[par] -> insert(w[v]);
	for(int u : adj[v]){	
		if(u != par){
			build(u, v, d+1);
		}
	}
}

int kth_anc(int v, int k){
	while(k){
		int p = k & -k;
		k -= p;
		const int lsb = __builtin_ctz(p);
		v = anc[v][lsb];
	}
	return v;
}

int lca(int v, int u){
	if(dep[v] < dep[u])
		swap(v, u);
	v = kth_anc(v, dep[v] - dep[u]);
	if(v == u)
		return v;
	
	for(int bit = 17; bit >= 0; bit--){
		if(anc[v][bit] != anc[u][bit])
			v = anc[v][bit], u = anc[u][bit];
	}// should end with both as direct children of lca
	return anc[v][0];
}

ll kth(int k, seg_tree* u, seg_tree* v, seg_tree* l, int l_idx, ll tl = -INF, ll tr = INF){
	if(tl == tr){
		return tl;
	}
	ll mid = tl + (tr - tl) / 2;
	int l_cnt = u -> left -> cnt + v -> left -> cnt - 2* l -> left -> cnt;
	if(w[l_idx] >= tl && w[l_idx] <= mid){// if removed lca twice
		l_cnt++;
	}
	if(l_cnt >= k)
		return kth(k, u -> left, v -> left, l -> left, l_idx, tl, mid);
	return kth(k - l_cnt, u -> right, v -> right, l -> right, l_idx, mid+1, tr);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("int", "r", stdin);//freopen("out", "w", stdout);
	roots[0] = new seg_tree();
	
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> w[i];
	for(int i = 1, u, v; i < n && cin >> u >> v; i++){
		adj[u].push_back(v), adj[v].push_back(u);
	}
	build(1);// root the tree at 1
	
	for(int i = 1, u, v, k; i <= m; i++){
		cin >> u >> v >> k;
		int l = lca(u, v);
		ll ans = kth(k, roots[u], roots[v], roots[l], l);
		cout << ans << "\n";
		//cout << flush;
	}
	return 0;
}
	
