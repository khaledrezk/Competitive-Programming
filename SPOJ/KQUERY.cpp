#include <bits/stdc++.h>
#define INF 1000'000'000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

vector < vector < int > > tree(120'010);

vector < int > combine(vector < int > & a, vector < int > & b){
	vector < int > ret;
	ret.reserve(a.size() + b.size());
	unsigned int i1 = 0, i2 = 0;
	while(i1 < a.size() && i2 < b.size()){
		if(a[i1] <= b[i2])
			ret.push_back(a[i1++]);
		else
			ret.push_back(b[i2++]);
	}
	while(i1 < a.size())
		ret.push_back(a[i1++]);
	while(i2 < b.size())
		ret.push_back(b[i2++]);
	return ret;
}

vector < int > a(30'010);

void build(int v = 1, int low = 0, int high = n-1){
	if(low == high){
		tree[v] = {a[low]};
		return;
	}
	int mid = low + (high - low) / 2;
	build(v*2, low, mid), build(v*2+1, mid+1, high);
	tree[v] =  combine(tree[v*2], tree[v*2+1]);
}

int cnt_greater(int k, vector < int > & v){
	return v.end() - upper_bound(v.begin(), v.end(), k);
}

int query(int l, int r, int k, int v = 1, int low = 0, int high = n-1){
	if(l > r)
		return 0;
	else if(l <= low && r >= high){
		return cnt_greater(k, tree[v]);
	}
	int mid = low + (high - low) / 2;
	int q1 = query(l, min(r, mid), k, v * 2, low, mid);
	int q2 = query(max(mid+1, l), r, k, v*2 + 1, mid+1, high);
	return q1 + q2;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);
	cin >> n;
	for(int i = 0; i < n; i++)	
		cin >> a[i];
	
	build();
	int q, l, r, k;
	cin >> q;
	while(q-- && cin >> l >> r >> k){
		auto ans = query(l-1,r-1,k);
		cout << ans << "\n";
	}
	return 0;
}

