#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define INF 2000'000'000
using namespace std; 
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
template<typename T> using ordered_set = tree<T , null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
constexpr int MXN = 300'005;

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


struct fenwick_tree{
	vector < int > T;
	int size;
	fenwick_tree(int n = 0){
		size = n;
		T.resize(size+1);
	}
	void add(int idx, int val){
		while(idx <= size){
			T[idx] += val, idx += idx &-idx;
		}
	}
	int pref_sum(int idx){
		int ans = 0;
		
		while(idx){
			ans += T[idx], idx -= idx & - idx;
		}
		return ans;
	}
	int rng_sum(int l, int r){
		return (pref_sum(r) - pref_sum(l-1));
	}
	void upd(int idx, int val){
		val -= rng_sum(idx, idx);
		add(idx, val);
	}
};

string s;
fenwick_tree paths(MXN*2);
int st_idx[MXN], end_idx[MXN], nxt_pos = 1;

void update(int v){
	paths.upd(st_idx[v], s[v]-'0');
	paths.upd(end_idx[v], -s[v]+'0');
}

void dfs2(int v = 0, int p = -1){
	st_idx[v] = nxt_pos++;
	for(int u : adj[v]){
		if(u != p){
			dfs2(u, v);
		}
	}
	end_idx[v] = nxt_pos++;
	if(s[v] == '1')
		update(v);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);//freopen("out", "w", stdout);
	int n, m;
	cin >> n >> m >> s;
	adj.assign(n+1, vector < int > (0));
	for(int i = 1, u, v; i < n && cin >> u >> v; i++){
		adj[u].push_back(v), adj[v].push_back(u);
	}
	build_lca(0);
	dfs2(0);
	for(int type, i, j; m-- && cin >> type >> i; ){
		if(type == 0){
			s[i] = s[i] == '1' ? '0' : '1';
			update(i);
		}
		else{
			cin >> j;
			int l = query_lca(i, j);
			/*int path = paths.rng_sum(st_idx[l], st_idx[i]);
			path += paths.rng_sum(st_idx[l], st_idx[j]);
			path -= s[l] == '1';*/
			int path = paths.pref_sum(st_idx[i]) + paths.pref_sum(st_idx[j]);
			path -= 2*paths.pref_sum(st_idx[l]-1) + (s[l] == '1');
			
			int pth_ln = dep[i] + dep[j] - 2*dep[l];
			cout << (path == pth_ln+1 || path == 0 ? "YES" : "NO") << "\n";
		}
	}
	return 0;
}
