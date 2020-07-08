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


constexpr ll CNT_PRIMES = 1, MOD = 1000'000'007;
const array < ll, CNT_PRIMES > primes = {1009};
vector < ll > p_pow[CNT_PRIMES];

struct suffix_hash{
	vector < ll > hash[CNT_PRIMES];
	suffix_hash(string & s){
		build(s);
		update_powers(s.size());
	}
	
	void update_powers(int n){
		int old = p_pow[0].size();
		if(old >= n)
			return;
		for(int p_idx = 0; p_idx < CNT_PRIMES; p_idx++){
			p_pow[p_idx].resize(n+1, 1);
			for(int i = max(1, old); i <= n; i++){
				p_pow[p_idx][i] = p_pow[p_idx][i-1] * primes[p_idx] % MOD;
			}
		}	
	}
	void build(string & s){
		int n = s.size();
		for(int p_idx = 0; p_idx < CNT_PRIMES; p_idx++){
			ll P = primes[p_idx];
			hash[p_idx].assign(n+1, 0);
			for(int i = n-1; i >= 0; i--){
				hash[p_idx][i] = (s[i] + hash[p_idx][i+1] * P) % MOD;
			}	
		}
	}
	array < ll, CNT_PRIMES> query(int start, int len){
		array < ll, CNT_PRIMES> ret;
		for(int p_idx = 0; p_idx < CNT_PRIMES; p_idx++){
			ret[p_idx] = hash[p_idx][start] - hash[p_idx][start+len]*p_pow[p_idx][len];
			ret[p_idx] %= MOD;
			if(ret[p_idx] < 0)
				ret[p_idx] += MOD;
		}
		return ret;
	}
};

