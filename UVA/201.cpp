#include<bits/stdc++.h>
#define INF 1000'000'000
using namespace std;
typedef  long long   ll;
typedef  unsigned long long ull;
typedef pair<int,int> pii;
int n,m;
int dx[] = {0, 1, 0, -1};// right, down, left, up
int dy[] = {1, 0,-1,  0};
map < pii, set < pii > > adj;
map < int,int > sq_size;
pii next(pii cur, int dir){
	cur.first += dx[dir], cur.second+=dy[dir];
	return cur;
}

int solve(pii v, int dir =0, int dep = 0){	
	if(dir == 4){// base case
		sq_size[dep]++;	
		return true;
	}
	if(dir == 0){// initial case
		int ans = 0;
		while(adj[v].find(next(v,0)) != adj[v].end())
			v = next(v,0), ans+= solve(v,dir+1, ++dep);
		return ans;
	}
	for(int i = 0; i < dep; i++, v = next(v,dir))
		if(adj[v].find(next(v,dir)) == adj[v].end())
			return false;
	return solve(v,dir+1, dep);
}

int main (){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("in", "r", stdin);
	//freopen("out", "w", stdout);
	for(int tc = 1;cin >> n >> m; tc++){
		if(tc != 1){
			cout << "\n**********************************\n\n";
		}
		adj.clear(), sq_size.clear();
		for(int i, j;m--; ){
			char c;
			cin >> c >> i >> j;
			pii p1,p2;
			(c == 'H') ? (p1 = {i,j}, p2 = {i,j+1}) : (p1 = {j,i}, p2 = {j+1,i});
			adj[p1].insert(p2), adj[p2].insert(p1);
		}
		int ans = 0;
		for(auto &p : adj)
			ans += solve(p.first);
		cout << "Problem #" << tc << "\n\n";
		for(auto p : sq_size){
			cout << p.second << " square (s) of size " << p.first << "\n";
		}
		if(sq_size.empty())
			cout << "No completed squares can be found.\n";
		
	}
	return 0;
}
