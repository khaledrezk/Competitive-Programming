#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define INF 2000'000'000
using namespace std; 
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
template<typename T> using ordered_set = tree<T , null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int MXN = 450'005;

template<typename T, T(*combine)(T, T)>
struct sparse_table{
	int n;
	vector < vector < T > > table;
	
	sparse_table(const int N, const vector < T > & v = {}): n(N){
		table.assign(__lg(n)+1, vector < T > (n));
		if(v.size())
			build_sparse_table(v);
	}
	
	void build_sparse_table(const vector < T > & v){
			
		for(int i = 0; i < n; i++)// for 0 based array
			table[0][i] = v[i];
		
		int mx_row = __lg(n);
		for(int row = 1; row <= mx_row; row++){
			int c_range = 1 << row;
			for(int col = 0; col + c_range - 1 < n; col++){
				table[row][col] = combine(table[row-1][col] , table[row-1][col + (c_range >> 1)]);
			}
		}
	}
	
	T query_o1(int l, int r){// overlap friendly
		if(l > r)
			swap(l,r);
		int msb = __lg(r - l + 1), s_range = 1 << msb;
		return combine(table[msb][l], table[msb][r - (s_range - 1)]);
	}
	
	T query_ologn(int l, int r){// non overlap friendly functions as +, * ..
		if(l > r)
			swap(l,r);
		T ans;
		bool started = 0;// not to add initall value to ans
		while(l <= r){
			int msb = __lg(r - l + 1);
			auto nxt = table[msb][l]; l += 1 << msb;
			if(started)
				ans = combine(ans, nxt);
			else
				ans = nxt, started = true;
		}
		return ans;
	}
};

vector < vector < int > > adj;


int dep[MXN], f_idx[MXN], l_idx[MXN];
vector < int > euler;

void dfs(int v, int par = -1, int d = 0){
	dep[v] = d;
	f_idx[v] = euler.size(); 
	euler.push_back(v);
	for(int u : adj[v]){
		if(u != par){
			dfs(u, v, d+1);
			euler.push_back(v);
		}
	}
	l_idx[v] = euler.size();
}

inline int min_dep(int a, int b){
	return dep[a] < dep[b] ? a : b;
}

sparse_table < int, min_dep > LCA(1);// init size

void build_lca(int root = 1){
	euler.clear();
	dfs(root);
	LCA = sparse_table < int, min_dep > (euler.size(), euler);
}

inline int query_lca(int v, int u){
	return LCA.query_o1(f_idx[v], f_idx[u]);// my sparse table handles order
}

bitset < 251 > clr[MXN];
void build_ans(int v, int par = -1){
	for(int u : adj[v]){
		if(u != par){
			build_ans(u, v);
			clr[v] |= clr[u];
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);//freopen("out", "w", stdout);
	int t;
	cin >> t;
	while(t--){
		int n, q, r;
		cin >> n >> q >> r;
		adj.assign(n+1, vector < int > (0));
		for(int i = 0, tmp; i < n; i++){
			clr[i].reset();
			cin >> tmp;
			clr[i][tmp] = 1;
		}
		for(int i = 1, u, v; i < n && cin >> u >> v; i++){
			adj[u].push_back(v), adj[v].push_back(u);
		}
		build_lca(r);
		build_ans(r);
		for(int i = 1, u, v; i <= q && cin >> u >> v; i++){
			int lca = query_lca(u, v);
			cout << clr[lca].count() << "\n";
		}
	}
	return 0;
}
