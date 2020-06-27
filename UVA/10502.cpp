#include<bits/stdc++.h>
#define INF 1000'000'000
using namespace std;
typedef  long long   ll;
typedef  unsigned long long ull;
vector < vector < int > > sum;
inline int sum_rect(int i1, int j1, int i2, int j2){
	return sum[i2][j2] - sum[i1-1][j2] - sum[i2][j1-1] + sum[i1-1][j1-1];
}
int main (){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("in", "r", stdin);
	//freopen("out", "w", stdout);
	int n, m;
	string s;
	while(cin >> n >> m && n && m){
		sum.assign(n+1,vector < int > (m+1)); 
		for(int i = 0; i < n && cin >> s; i++)
			for(int j = 0; j < m; j++)
				sum[i+1][j+1] = s[j] & 1;
		
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				sum[i][j] += sum[i][j-1];
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				sum[i][j] += sum[i-1][j];
		int ans = 0;
		for(int i1 = 1; i1 <= n; i1++)
			for(int j1 = 1; j1 <= m; j1++)
				for(int i2 = i1; i2 <= n; i2++)
					for(int j2 = j1; j2 <= m; j2++)
						if(sum_rect(i1,j1,i2,j2) == (i2-i1+1)*(j2-j1+1))
							++ans;

		cout << ans << "\n";
	}
	return 0;
}
