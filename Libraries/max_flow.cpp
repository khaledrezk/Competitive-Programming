#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define INF 2000'000'000
using namespace std; 
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
template<typename T> using ordered_set = tree<T , null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int MXN = 1005;

int adj_mat[MXN][MXN];
vector < int > adj_list[MXN];

vector < int > path;

bitset < MXN > vis;
int prv[MXN];

int get_path_bfs(int src, int sink){
	queue < int > q;
	q.push(src);
	vis[src] = 1, prv[src] = -1;
	while(!q.empty()){
		int v = q.front();
		q.pop();
		for(int u : adj_list[v]){
			if(!vis[u] && adj_mat[v][u] > 0){
				vis[u] = 1, prv[u] = v, q.push(u);
				if(u == sink){
					goto END_LOOP;
				}
			}
		}
	}
	END_LOOP:
	if(!vis[sink]){
		return 0;
	}
	for(int v = sink; v != -1; v = prv[v])
		path.push_back(v);
	reverse(path.begin(), path.end());
	int flow = INF;
	for(int i = 0; i + 1 < (int)path.size(); i++)
		flow = min(flow, adj_mat[path[i]][path[i+1]]);
	return flow;
}

int max_flow(int src, int sink){
	int ans = 0;
	while(true){
		ll cur = get_path_bfs(src, sink);
		if(cur == 0){
			break;
		}
		ans += cur;
		for(int i = 0; i + 1 < (int)path.size(); i++){
			adj_mat[path[i]] [path[i+1]] -= cur;
			adj_mat[path[i+1]] [path[i]] += cur;
		}
		path.clear(), vis.reset();
	}
	return ans;
}

void add_edge(int u, int v, int w = 1){
	adj_mat[u][v] += w;
	if(adj_mat[u][v] != w)// already added to adj list
		return;
	adj_list[u].push_back(v);
	adj_list[v].push_back(u);
}
