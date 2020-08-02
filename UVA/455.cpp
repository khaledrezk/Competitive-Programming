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

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);
	int t;
	cin >> t;
	string s;
	
	for(int tc = 1; tc <= t && cin >> s; tc++){
		if(tc != 1)
			cout << "\n";
		int n = s.size();
		vector < int > factors;
		for(int i = 1; i * i <= n; i++){
			if(n % i == 0){
				factors.push_back(i);
				if(n/i != i)
					factors.push_back(n/i);
			}
		}
		sort(factors.begin(), factors.end());
		int ans = n;
		for(int fc : factors){
			bool valid = true;
			for(int i = fc; i < n && valid; i++){
				if(s[i] != s[i%fc])
					valid = false;
			}
			if(valid){
				ans = fc;
				break;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
