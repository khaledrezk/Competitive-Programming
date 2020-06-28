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


template<typename T>
struct sparse_table{
	int n;
	vector < vector < T > > table;
	T (*combine) (T,T);
	
	sparse_table(int N, vector < T > & v, T (*comb) (T,T)){
		n = N, combine = comb;
		table.assign(__lg(n)+1, vector < T > (n));
		build_sparse_table(v);
	}
	void build_sparse_table(const vector < T > & v){
			
		for(int i = 0; i < n; i++)// for 0 based array
			table[0][i] = v[i];
		
		int mx_row = __lg(n);
		for(int row = 1; row <= mx_row; row++){
			int c_range = 1 << row;
			for(int col = 0; col + c_range - 1 < n; col++){
				table[row][col] = combine(table[row-1][col] , table[row-1][col + (c_range >> 1)]);
			}
		}
	}
	
	T query_o1(int l, int r){// overlap freindly
		if(l > r)
			swap(l,r);
		int msb = __lg(r - l + 1), s_range = 1 << msb;
		return combine(table[msb][l], table[msb][r - (s_range - 1)]);
	}
	
	T query_ologn(int l, int r){// non overlap friendly functions as +, * ..
		if(l > r)
			swap(l,r);
		T ans;
		bool started = 0;// not to add initall value add 
		while(l <= r){
			int msb = __lg(r - l + 1);
			auto nxt = table[msb][l]; l += 1 << msb;
			if(started)
				ans = combine(ans, nxt);
			else
				ans = nxt, started = true;
		}
		return ans;
	}
};

vector < int > a(1e5+5);

int combine(int l, int r){
	return a[l] >= a[r] ? l : r;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);
	ll n, ans = 0;
	cin >> n;
	vector < int > tmp(n+1);
	vector < ll >  dp(n+1);
	for(int i = 1; i  < n; i++){
		cin >> a[i];
		tmp[i] = i;
	}
	tmp[n] = n;
	sparse_table<int> st(n+1, tmp, combine);
	for(int i = n-1; i >= 1; i--){
		// find max in range i to a[i]
		int mx = st.query_o1(i+1, a[i]);
		if(a[i] >= n)
			dp[i] = n - i;
		else
			dp[i] = mx - i + n - a[i] + dp[mx];
		ans += dp[i];
	}
	cout << ans << endl;
	return 0;
}
