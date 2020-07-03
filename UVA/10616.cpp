#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
#define INF 2000'000'000

using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef tree<int, null_type,less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
vector < int > v(201);
ll n, q, d, m;
ll memo[201][11][20];
ll solve(int i, int cnt, int mod){
	if(cnt == 0)
		return mod == 0;
	else if(i == n)// cnt != 0
		return 0;
	else if(memo[i][cnt][mod] != -1)
		return memo[i][cnt][mod];
	ll leave = solve(i+1, cnt, mod);
	ll pick  = solve(i+1, cnt - 1, ((mod - v[i])%d + d) % d);
	return memo[i][cnt][mod] = leave + pick;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);
	for (int tc = 1; cin >> n >> q && (n || q); tc++){
		for(int i = 0; i < n; i++)
			cin >> v[i];
		cout << "SET " << tc << ":\n";
		for(int i = 1; i <= q && cin >> d >> m; i++){
			memset(memo, -1, (201)*(11)*(20)*sizeof(ll));
			cout << "QUERY " << i << ": " << solve(0, m, 0) << "\n"; 
		}
	}	
	return 0;
}
