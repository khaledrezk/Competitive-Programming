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

int solve(string& s){// using prefix function of kmp
	int n = s.size(), sz = 2*n+1, ans = 0, border = 0;
	s += "@" + string(s.rbegin(), s.rend());
	
	vector < int > pref(sz);
	for(int i = 1; i < sz; i++){
		while(border > 0 && s[i] != s[border])
			border = pref[border-1];
		if(s[i] == s[border])
			border++;
		pref[i] = border;
		if(i >= n && border > ans)
			ans = border;
	}
	return ans;
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);
	//freopen("out", "w", stdout);
	string s;
	int t;
	cin >> t;
	for(int tc = 1; tc <= t && cin >> s; tc++){
		int ans = solve(s);
		for(int i = ans-1; i >= 0; i--)
			cout << s[i];
		cout << "\n";
		//cout << flush;
	}
	return 0;
}
