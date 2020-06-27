#include <bits/stdc++.h>
#define INF 1000'000'000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int dx[] = {1,-1,0,0};
int dy[] = {0,0, 1, -1};

int t,n, m;

bool valid(int i, int j){
	return i >= 0 && i < n && j >= 0 && j < m;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("in", "r", stdin);
	cin >> t;
	while(t-- && cin >> n >> m){
		vector < string > grid(n);
		vector < vector < int > > ans(n, vector < int > (m, INF));
		for(string & s : grid)
			cin >> s;
		
		// bfs
		queue < pair<int,int> > q;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				if(grid[i][j] == '1')
					q.push({i,j}), ans[i][j] = 0;
		for(int level = 0; !q.empty(); level++){
			int sz = q.size();
			while(sz--){
				auto v = q.front(); q.pop();
				for(int i = 0; i < 4; i++){
					int nx = v.first + dx[i], ny = v.second + dy[i];
					if(valid(nx, ny) && ans[nx][ny] > level +1)
						q.push({nx, ny}), ans[nx][ny] = level + 1;
				}
			}
		}
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				cout << ans[i][j] << (j == m-1 ? "\n" : " ");
	}
	return 0;
}
