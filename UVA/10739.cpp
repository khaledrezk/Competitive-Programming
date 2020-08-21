#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
//#define INF 2000'000'000
#define INF 2e9
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef tree<int, null_type,less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
string s;
int n;
int dp[1001][1001];

int solve(){
	for(int len = 2; len <= n; len++){
		for(int l = 0, r = len-1; r < n; l++, r++){
			dp[l][r] = INF;
			if(s[l] == s[r])// match
				dp[l][r] = dp[l+1][r-1];
			// remove first or
			dp[l][r] = min(dp[l][r], dp[l+1][r] + 1);
			// remove last
			dp[l][r] = min(dp[l][r], dp[l][r-1] + 1);
			// replace 
			dp[l][r] = min(dp[l][r], dp[l+1][r-1] + 1);
		}
	}
	return dp[0][n-1];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);freopen("out", "w", stdout);
	int t;
	cin >> t;
	
	for(int tc = 1;t-- && cin >> s; tc++){
		n = s.size();
		cout << "Case " << tc << ": " << solve() << "\n";
	}
	return 0;
}
