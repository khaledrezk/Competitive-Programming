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

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);
	int n, q, l, r;
	cin >> n;
	vector < int > v(n);
	for(int & i : v)
		cin >> i;
	sparse_table<int> st(n, v, [](int a, int b){return min(a,b);});
	
	cin >> q;
	while(q-- && cin >> l >> r){
		cout << st.query_o1(l, r) << "\n";
	}
	return 0;
}
