#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define INF 2000'000'000
#define MOD 1000'000'007
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


matrix mat_pow(matrix m, int p){
	matrix ans(2, vector < ll > (2));
	ans[0][0] = ans[1][1] = 1;
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
	matrix m = {{1,1}, {1,2}};
	matrix f1 = {{1}, {2}};
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		auto p = mat_pow(m, n-1);
		auto ans = mat_mul(p, f1);
		
		cout << (((ans[0][0] - n) % MOD + MOD) % MOD) << "\n";
		//cout << flush;
	}
	return 0;
}
