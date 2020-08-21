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

ull dp[5005];

ull solve(){
	int n = s.size();
	dp[n] = 1;
	for(int i = n-1; i >= 0; i--){
		if(s[i] == '0'){
			dp[i] = 0;
		}
		else if(s[i+1] == '0'){
			dp[i] = dp[i+2];
		}
		else{
			dp[i] = dp[i+1];
			if(i + 1 < n && stoi(s.substr(i, 2)) <= 26)
				dp[i] += dp[i+2];	
		}
	}
	return dp[0];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);freopen("out", "w", stdout);
	while(cin >> s && s != "0"){
		cout << solve() << "\n";
	}
	return 0;
}
