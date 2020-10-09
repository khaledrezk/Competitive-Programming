#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
#define INF 2000'000'000
using namespace std; 
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
template<typename T> using ordered_set = tree<T , null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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




constexpr int MXN = 100'005;
vector < vector < int > > adj;
int n, m, clr[MXN], dep[MXN], nd_s1[MXN], nd_e1[MXN], nd_s2[MXN], nd_e2[MXN];

vector < int > euler1, euler2;

void dfs(int v, int d = 1){
	dep[v] = d;
	
	nd_s1[v] = euler1.size(), euler1.push_back(v);
	nd_s2[v] = euler2.size(), euler2.push_back(v);
	for(int u : adj[v]){
		if(!dep[u]){
			dfs(u, d+1);
			euler1.push_back(v);
		}
	}
	
	nd_e1[v] = euler1.size(), euler1.push_back(v);
	nd_e2[v] = euler2.size(), euler2.push_back(v);
}

inline int min_depth(int a, int b){
	return dep[a] < dep[b] ? a : b;
}

sparse_table < int, min_depth > LCA(1);

void build_lca(){
	LCA = sparse_table<int, min_depth> (euler1.size(), euler1);
}

void init_graph(){
	euler1.clear(), euler2.clear();
	dfs(1);
	build_lca();
}

constexpr int SQ = 512;

struct query{
	int l, r, c, idx;
	
	bool operator< (const query& RHS)const{
		if(l / SQ != RHS.l / SQ)
			return l / SQ < RHS.l / SQ;
		return r < RHS.r;
	}
};

vector < query > queries;
vector < bool > ans, vis;
int freq[MXN];

int s = 0, e = -1;

void add(int idx){
	idx = euler2[idx];
	freq[clr[idx]] += vis[idx] ? -1 : 1;
	vis[ idx ] = vis[ idx ] ^ 1;		
}

void solve(query& q){
	while(e < q.r)
		add(++e);
	while(s > q.l)
		add(--s);
	while(e > q.r)
		add(e--);
	while(s < q.l)
		add(s++);
	ans[q.idx] = freq[q.c];
	/*cout << "vis:";
	for(int i = 1; i <= n; i++)
		if(vis[i])
			cout << i << " ";
	cout << "Cur ans :" << ans[q.idx] << endl;
	cout << endl << endl;*/
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);//freopen("out", "w", stdout);
	adj.reserve(MXN);
	euler1.reserve(MXN*4);
	euler2.reserve(MXN*2);
	queries.reserve(MXN*2);

	while(cin >> n >> m){
		adj.assign(n+1, vector <int> (0));
		ans.assign(m+1, 0), vis.assign(n+1, 0);
		s = 0, e = -1;

		for(int i = 1; i <= n; i++){
			cin >> clr[i];
		}
				
		for(int i = 1, u, v; i < n && cin >> u >> v; i++){
			adj[u].push_back(v), adj[v].push_back(u);
		}
		init_graph();

		for(int i = 0, u, v, c; i < m && cin >> u >> v >> c; i++){
			int lca = LCA.query_o1(nd_s1[u], nd_s1[v]);
			//cout << "Lca between :" << u << ", " << v << " => " << lca << "clr:" << clr[lca] << endl;

			if(clr[lca] == c){
				ans[i] = 1;
			}
			else{
				if(nd_s2[u] > nd_s2[v])
					swap(u, v);
				// u has min index
				int l, r;
				if(lca == u || lca == v){
					// start to start
					l = nd_s2[u], r = nd_s2[v];
				}
				else{
					// end to start
					l = nd_e2[u], r = nd_s2[v];
				}
				//cout << "Query :" << i << " range {" << l << ", " << r << "}\n";
				queries.push_back({l, r, c, i});
			}
		}
		
		sort(queries.begin(), queries.end());
		for(auto q : queries){
			solve(q);
		}
		
		for(int i = 0; i < m; i++)
			cout << (ans[i] ? "Find" :  "NotFind") << "\n";
		memset(dep, 0, (n+2)*sizeof(int));
		memset(freq, 0, (n+2) * sizeof(int));
		queries.clear();
		
	}
	return 0;
}
