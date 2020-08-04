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

vector < int > prefix(string s){
	int n = s.size(), border = 0;
	vector < int > pref(n);
	for(int i = 1; i < n; i++){
		while(border > 0 && s[i] != s[border])
			border = pref[border-1];
		if(s[i] == s[border])
			border++;
		pref[i] = border;
	}
	return pref;
}

bool valid(int len, string & s){
	string tmp = s.substr(0, len);
	auto pref = prefix(string(tmp.rbegin(), tmp.rend()) + "@" + s);
	for(int i : pref)
		if(i == len)
			return true;
	return false;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);
	//("out", "w", stdout);
	string s;
	
	int t;
	cin >> t;
	for(int tc = 1; tc <= t && cin >> s; tc++){
		int ans = 1, n = s.size();
		for(int low = 2, high = n; low <= high; ){
			int mid = low + (high - low) / 2;
			if(valid(mid, s))
				ans = mid, low = mid+1;
			else
				high = mid-1;
		}
		for(int i = ans-1; i >= 0; i--)
			cout << s[i];
		cout << "\n";
		//cout << flush;
	}
	return 0;
}
