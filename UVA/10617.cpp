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
ll dp[1001][1001];

ll solve(){
	for(int len = 1; len <= n; len++){
		for(int l = 0, r = len-1; r < n; l++, r++){
			if(len == 1){
				dp[l][r] = 1;
			}
			else if(len == 2){
				dp[l][r] = 2 + (s[l] == s[r]);
			}
			else{
				// remove intersection with from [l+1] to [r-1]
				dp[l][r] = dp[l+1][r] + dp[l][r-1] - dp[l+1][r-1];
				if(s[l] == s[r]){
					// add 1 to only choosing l and r as palindrome 
					dp[l][r] += dp[l+1][r-1] + 1;
				}
			}
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
		cout << solve() << "\n";
		//cout << flush;
	}
	return 0;
}
