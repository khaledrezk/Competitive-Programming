#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define INF 2000'000'000

using namespace std; 
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
template<typename T> using ordered_set = tree<T , null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct segmentTree{
	vector < int > T;
	int size;
	segmentTree(int n){
		for(size = 2; size < n; size *= 2);
		T.assign(size*2,-INF);
	}
	
	void update(int pos, int val, int id, int tl, int tr){
		if(pos > tr || pos < tl)
			return;
		else if(tl == tr){
			T[id] = val;
			return;
		}
		int mid = tl + (tr - tl) / 2;
		update(pos, val, id*2+1, tl, mid);
		update(pos, val, id*2+2, mid+1, tr);
		T[id] = max(T[id*2+1], T[id*2+2]);
	}
	void update(int pos, int val){
		update(pos, val, 0, 0, size-1);
	}
	
	int query(int l, int r, int id, int tl, int tr){
		if(l > tr || r < tl)
			return -INF;
		else if( l <= tl && r >= tr)
			return T[id];
		int mid = tl + (tr - tl) / 2;
		return max(query(l, r, id*2+1, tl, mid),
				   query(l, r, id*2+2, mid+1, tr));
	}
	
	int query(int l, int r){
		return query(l, r, 0, 0, size-1);
	}
	
	
};

struct HLD{
	#define VAL_ON_EDGES 1 // make 1 if values on edges
	const vector < vector < int > > &adj;
	vector < int > dep, par, root, pos, cntChildren, chld;
	int nxt_pos;
	HLD(int n, const vector < vector < int >> & G, int treeRoot = 1): adj(G){
		nxt_pos = 1;
		dep.resize(n+5);
		par.resize(n+5);
		root.resize(n+5);
		pos.resize(n+5);
		cntChildren.resize(n+5);
		chld.resize(n+5);
		init(treeRoot);
		build(treeRoot);
	}
	
	void init(int v, int p = -1, int d = 0){
		dep[v] = d;
		par[v] = p;
		cntChildren[v] = 1;
		for(int u : adj[v]){
			if(u != p){
				init(u, v, d+1);
				cntChildren[v] += cntChildren[u];
				if(cntChildren[u] > cntChildren[chld[v]])
					chld[v] = u;
			}		
		}
	}
	
	void build(int v, bool newChain = true){
		root[v] = newChain ? v : root[par[v]];
		pos[v] = nxt_pos++;
		if(chld[v])
			build(chld[v], false);
		for(int u : adj[v]){
			if(u != chld[v] && u != par[v])
				build(u, true);
		}
	}
	
	inline pair<int,int> moveUp(int& v){//move up the chain and also change to next position
		pair<int,int> ans = {pos[root[v]], pos[v]};
		v = par[root[v]];
		return ans;
	}
	
	inline void makeULower(int & u, int & v){
		if(dep[root[u]] < dep[root[v]] || (root[u] == root[v] && dep[u] < dep[v])){
			swap(u, v);	
		}
	}
	
	vector < pair<int,int>> queryPath(int u, int v){
		// return all ranges to query in segment tree
		vector < pair<int,int>> ans;
		while(root[u] != root[v]){
			makeULower(u,v);
			ans.push_back(moveUp(u));
		}
		// add range between u, v
		makeULower(u,v);
		if(!VAL_ON_EDGES)// value on nodes
			ans.push_back({pos[v], pos[u]});
		else if(u != v){// don't include the root node.
			ans.push_back({pos[v]+1, pos[u]});
			
		}
		return ans;
	}
	
};


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("in", "r", stdin);
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		vector < vector < int > > adj(n+5);
		vector < tuple < int,int,int> > edges(n-1);
		for(auto & [u,v,w] : edges){
			cin >> u >> v >> w;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		HLD h(n, adj);
		segmentTree st(n+5);
		for(auto & [chld,par,w] : edges){
			if(h.dep[par] > h.dep[chld])
				swap(par, chld);
			// u is always the child
			st.update(h.pos[chld], w);
		}
		string type;
		while(cin >> type && type[0] != 'D'){
			int u, v;
			cin >> u >> v;
			if(type[0] == 'C'){
				auto & [chld,_,__] = edges[u-1];
				st.update(h.pos[chld], v);
			}
			else{// query
				auto rngs = h.queryPath(u,v);
				int ans = -INF;
				for(auto & [l,r] : rngs){
					auto cur = st.query(l,r);
					ans = max(ans, cur);
				}
				cout << ans << "\n";
				
			}
		}
	}
	return 0;
	
}
