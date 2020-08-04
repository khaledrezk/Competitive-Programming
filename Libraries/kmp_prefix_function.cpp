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

vector < int > prefix(string& s){// using prefix function of kmp
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
