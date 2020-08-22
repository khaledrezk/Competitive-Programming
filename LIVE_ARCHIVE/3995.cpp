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

int mat[15][15];
int n;

bitset < 15 > prev_msk( bitset < 15 > cur){
	bitset < 15 > ans;
	for(int i = 0; i < 15; i++){
		if((!cur[i]) && (i == 0 || !cur[i-1]) && (i == 14 || !cur[i+1]))
			ans[i] = 1;
	}
	return ans;
}

int memo[15][1 << 15];

int solve(int row, bitset < 15 > msk){
	int & ret = memo[row][msk.to_ulong()];
	if(ret != -1)
		return ret;
	ret = 0;
	bool valid = 1;// mask has no 11 
	for(int i = 1; i < 15; i++){
		if(msk[i] && msk[i-1])
			valid = false;
	}
	if(valid){
		for(int i = 0; i < 15; i++){
			if(msk[i]){
				ret += mat[row][i];
			}
		}
		if(row)
			ret += solve(row-1, prev_msk(msk));
	}
	// try all submasks
	for(int i = 0; i < 15; i++){
		if(msk[i]){
			msk[i] = 0;
			ret = max(ret, solve(row, msk));
			msk[i] = 1;
		}
	}

	return ret;
}

void init(const vector < string > & stream){
	memset(mat, 0, 15*15*sizeof(int));
	memset(memo, -1, 15*(1<<15)*sizeof(int));
	
	if(stream.empty())
		return;
	n = stream.size();
	for(int i = 0; i < n; i++){
		stringstream ss(stream[i]);
		for(int j = 0; j < n; j++)
			ss >> mat[i][j];
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);//freopen("out", "w", stdout);
	string s;
	vector < string > stream;
	while(getline(cin, s)){
		if(s.empty()){
			init(stream);
			stream.clear();
			cout << solve(n-1, (1 << n) - 1) << "\n";
		}
		else{
			stream.push_back(s);
		}
	}
	if(!stream.empty()){
		init(stream);		
		cout << solve(n-1, (1 << n) - 1) << "\n";
	}
	return 0;
}
