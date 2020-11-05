#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define INF 2000'000'000
using namespace std; 
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
template<typename T> using ordered_set = tree<T , null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct segment_tree{
	vector < int > T;
	int size;
	segment_tree(int n){
		for(size = 2; size <= n; size*=2);
		T.assign(size*2, -INF);
	}
	
	void assign(int i, int val, int id, int tl, int tr){
		if(tl > i || tr < i)
			return;
		else if(tl == tr){
			T[id] = val;
			return;
		}
		int mid = tl + (tr - tl) / 2;
		assign(i, val, id*2+1, tl, mid);
		assign(i, val, id*2+2, mid+1, tr);
		T[id] = max(T[id*2+1], T[id*2+2]);
	}
	
	void assign(int i, int val){
		assign(i, val, 0, 0, size-1);
	}
	
	int rmq(int l, int r, int id, int tl, int tr){
		if(l > tr || r < tl)
			return -INF;
		else if(l <= tl && r >= tr)
			return T[id];
		int mid = tl + (tr - tl) / 2;
		int q1 = rmq(l, r, id*2+1, tl, mid);
		int q2 = rmq(l, r, id*2+2, mid+1, tr);
		return max(q1, q2);
	}
	
	int rmq(int l, int r){
		return rmq(l, r, 0, 0, size-1);
	}
};


constexpr int MXN = 10005;

struct edge{
	int t, w, idx;
};


vector < vector < edge >> adj;

int par[MXN], dep[MXN], edge_nd[MXN], tr_sz[MXN];
edge chld[MXN];

void dfs1(int v = 1, int p = -1, int d = 0){
	par[v] = p, dep[v] = d;
	tr_sz[v] = 1;
	edge bst = {0, -INF, 0};
	for(auto& e : adj[v]){
		if(e.t != p){
			edge_nd[e.idx] = e.t;
			dfs1(e.t, v, d+1);
			tr_sz[v] += tr_sz[e.t];
			if(tr_sz[e.t] > tr_sz[bst.t])	
				bst = e;
		}
	}
	chld[v] = bst;
}

int pos[MXN], root[MXN], nxt_pos = 1;

segment_tree st(1);

void build_hld(int v, int p = -1, int rt = -1, int w = -INF){
	if(rt == -1)
		rt = v;
	root[v] = rt;
	pos[v] = nxt_pos++;
	st.assign(pos[v], w);
	if(chld[v].t){
		build_hld(chld[v].t, v, rt, chld[v].w);
	}
	for(auto &e : adj[v]){
		if(e.t != p && e.t != chld[v].t){
			build_hld(e.t, v, -1, e.w);
		}
	}
}

int query(int l, int r){
	int p1 = pos[l], p2 = pos[r];
	if(p1 == p2)
		return -INF;
	
	if(root[l] == root[r]){
		if(p1 > p2)
			swap(p1, p2);
		return st.rmq(p1+1, p2);
	}
	else if(dep[root[l]] > dep[root[r]]){// move l up
		return max(st.rmq(pos[root[l]], pos[l]), query(par[root[l]], r));
	}
	return max(st.rmq(pos[root[r]], pos[r]), query(l, par[ root[ r]]));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("int", "r", stdin);//freopen("out", "w", stdout);
	int t, n;
	cin >> t;
	string type;
	while(t--){
		cin >> n;
		st = segment_tree(n+1);
		nxt_pos = 1;
		adj.assign(n+1, vector < edge> (0));
		for(int i = 1, u, v, w; i < n && cin >> u >> v >> w; i++){
			adj[u].push_back({v,w,i}), adj[v].push_back({u, w, i});
		}
		dfs1();
		build_hld(1);
		int l, r;
		while(cin >> type){
			if(type[0] == 'D')
				break;
			cin >> l >> r;
			if(type[0] == 'C'){
				st.assign(pos[edge_nd[l]], r);
			}
			else if(type[0] == 'Q'){
				cout << query(l, r) << "\n";
			}
		}		
	}
	return 0;
}
