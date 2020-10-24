#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define INF 2000'000'000
using namespace std; 
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
template<typename T> using ordered_set = tree<T , null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct node{
	int cntb;
	bool pref, suf;
	node(int b = 0, bool pr = 1, bool s = 1){
		cntb = b, pref = pr, suf = s;
	}
};

struct segment_tree{
	vector < node > T;
	int size;
	segment_tree(int n){
		for(size = 2; size < n; size *= 2);
		T.resize(2*size);
	}
	// initially all is white no need to build
	node operation(node & l, node & r){
		int cb = l.cntb + r.cntb - (l.suf == 0 && r.pref == 0);
		int prf = l.pref, suf = r.suf;
		return node(cb, prf, suf);
	}
	
	void flip(int i, int id, int tl, int tr){
		if(tl > i || tr < i)
			return;
		else if(tl == tr){
			if(T[id].cntb == 0)
				T[id] = node(1, 0, 0);
			else
				T[id] = node(0,1,1);
			return;
		}
		int mid = tl + (tr - tl) / 2;
		flip(i, id*2, tl, mid);
		flip(i, id*2+1, mid+1, tr);
		T[id] = operation(T[id*2], T[id*2+1]);
	}
	void flip(int i){
		flip(i,1,0,size-1);
	}
	
	node cnt_black(int l, int r, int id, int tl, int tr){
		if(l > tr || r < tl)
			return node(0,1,1);
		else if(l <= tl && r >= tr){
			return T[id];
		}
		int mid = tl + (tr - tl) / 2;
		auto q1 = cnt_black(l, r, id*2, tl, mid);
		auto q2 = cnt_black(l, r, id*2+1, mid+1, tr);
		return operation(q1, q2);
	}
	
	int cnt_black(int l, int r){
		return cnt_black(l,r, 1, 0, size-1).cntb;
	}
	
	void print(){
		cout << "Size :" << size << endl;
		for(int i = 1; i < 2*size; i++){
			cout << i << " :{" << T[i].cntb << " , " << T[i].pref << ", " << T[i].suf << "}\n";
		}
		cout << endl;
	}
};


vector < vector < int > > adj;

int timer = 0;
int st[100'005], en[100'005];

void dfs(int v, int par = 0){
	st[v] = timer++;
	for(int u : adj[v]){
		if(u != par){
			dfs(u, v);
		}
	}
	en[v] = timer++;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);//freopen("out", "w", stdout);
	
	adj.reserve(1e5+5);
	
	int t, n, m;
	cin >> t;
	
	while(t--){
		cin >> n >> m;
		adj.assign(n+1, vector < int > (0));
		for(int i = 1, u, v; i < n && cin >> u >> v; i++){
			adj[u].push_back(v), adj[v].push_back(u);
		}
		dfs(1);
		segment_tree euler(timer+1);
		for(int i = 1, op, v; i <= m && cin >> op >> v; i++){
			if(op == 1){
				euler.flip(st[v]), euler.flip(en[v]);
			}
			else{
				cout << euler.cnt_black(st[v], en[v]) << "\n";
			}
		}
	}
	return 0;
}
