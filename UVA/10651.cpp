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

int memo[1 << 12];

int solve(int msk){
	int & ret = memo[msk];
	if(ret != -1)
		return ret;
	ret = __builtin_popcount(msk);
	for(int i = 0; i <= 10; i++){
		if((msk >> i) & 1  && (msk >> (i+1) & 1)){
			int nw_msk = msk ^ (1 << i) ^ (1 << (i+1));
			if(i && (~msk >> (i-1)) & 1){
				ret = min(ret, solve(nw_msk | (1 << (i-1))));
			}
			if(i < 10 && (~msk >> (i+2)) & 1){
				ret = min(ret, solve(nw_msk | (1 << (i+2))));
			}
		}
	}
	return ret;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);freopen("out", "w", stdout);
	int t;
	string s;
	cin >> t;
	memset(memo, -1, (1 << 12) * sizeof(int));
	
	while(t-- && cin >> s){
		int msk = 0;
		for(int i = 0; i < 12; i++){
			if(s[i] == 'o')
				msk |= 1 << i;
		}
		cout << solve(msk) << "\n";
		//cout << flush;
	}
	return 0;
}
