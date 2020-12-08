#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define INF 2000'000'000
#define MOD 1000'000'000
using namespace std; 
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
template<typename T> using ordered_set = tree<T , null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef vector < vector < ll>> matrix;

matrix mat_mul(matrix& a, matrix& b){
	int r1 = a.size(), md = b.size(), c2 = b[0].size();
	matrix ans(r1, vector < ll > (c2));
	for(int i = 0; i < r1; i++){
		for(int j = 0; j < c2; j++){
			for(int k = 0; k < md; k++){
				ans[i][j] += a[i][k] * b[k][j];
				ans[i][j] %= MOD;
			}
		}
	}
	return ans;
}

int k;

matrix mat_pow(matrix m, int p){
	matrix ans(k, vector < ll > (k));
	for(int i = 0; i < k; i++)
		ans[i][i] = 1;
	while(p){
		if(p & 1)
			ans = mat_mul(ans, m);
		m = mat_mul(m,m), p /= 2;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> k;
		vector < ll > b(k), c(k);	
		for(ll & i : b)
			cin >> i;
		for(ll & i : c)
			cin >> i;
		cin >> n;
		if(n <= k){
			cout << b[n-1] << "\n";
			continue;
		}
		// build matrix
		matrix m(k, vector < ll > (k)), init(k);
		m[0] = c;
		for(int i = 1; i < k; i++)
			m[i][i-1] = 1;
		for(int i = 0; i < k; i++)
			init[i].push_back(b[k-i-1]);
		auto nw = mat_pow(m, n-k);
		auto ans = mat_mul(nw, init);
		cout << ans[0][0] << "\n";
	}
	return 0;
}
