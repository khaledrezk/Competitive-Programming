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

int period(string s){// using prefix function of KMP algorithm O(size)
	int n = s.size(), border = 0;
	vector < int > pref(n);
	for(int i = 1; i < n; i++){
		while(border > 0 && s[i] != s[border])// fail on previous border
			border = pref[border- 1];
		if(s[i] == s[border])
			border++;
		pref[i] = border;
	}
	
	if(n % ( n - pref[n-1]) == 0)
		return n - pref[n-1];
	return n;
}

int solve(string s){
	int n = s.size();
	vector < int > dp(n+1);// dp[i] is answer for prefix of length i	
	for(int i = 1; i <= n; i++){
		dp[i] = dp[i-1] + 1;
		for(int cur_len = 1; cur_len <= i; cur_len++){			
			int p = period(s.substr(i-cur_len, cur_len));
			if(p != cur_len)
				p = solve(s.substr(i-cur_len, p));
			dp[i] = min(dp[i], dp[i-cur_len] + p);
		}
	}
		
	return dp[n];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);
	//freopen("out", "w", stdout);
	string s;
	
	while(cin >> s && s != "*"){
		cout << solve(s) << "\n";
	}
	return 0;
}
