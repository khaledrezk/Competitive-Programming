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

vector < int > prefix(string & s){
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

vector < vector < int > > factors(2001);

void build_factors(){
	for(int i = 1; i <= 2000; i++)
		for(int j = 1; j * j <= i; j++){
			if(i % j == 0)// don't care of repetition
				factors[i].push_back(j), factors[i].push_back(i/j);
		}
	
	
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);
	//freopen("out", "w", stdout);
	string s;
	build_factors();
	int t;
	cin >> t;
	for(int tc = 1; tc <= t && cin >> s; tc++){
		int n = s.size();
		auto pref = prefix(s);
		int mn = (n+3) / 3, mx = n / 2;
		int ans = mx; // assuming that answer exist
		for(int i = mn; i <= mx; i++){
			for(int fc : factors[i]){
				if(pref[fc*2-1] == fc && pref.back() >= (n-fc)){
					ans = i;
					goto EXIT_LOOP;
				}
			}
		}
		EXIT_LOOP:
		for(int i = n; i < n+8; i++){
			cout << s[i%ans];
		}
		cout << "...\n";
	}
	return 0;
}
