#include <bits/stdc++.h>
#define INF 1000'000'000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;


template<typename T, T(*combine)(T, T)>
struct sparse_table{
	int n;
	vector < vector < T > > table;
	
	sparse_table(const int N, const vector < T > & v = {}): n(N){
		table.assign(__lg(n)+1, vector < T > (n));
		if(v.size())
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
	
	T query_o1(int l, int r){// overlap friendly
		if(l > r)
			swap(l,r);
		int msb = __lg(r - l + 1), s_range = 1 << msb;
		return combine(table[msb][l], table[msb][r - (s_range - 1)]);
	}
	
	T query_ologn(int l, int r){// non overlap friendly functions as +, * ..
		if(l > r)
			swap(l,r);
		T ans;
		bool started = 0;// not to add initall value to ans
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
