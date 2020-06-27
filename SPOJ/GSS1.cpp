#include <bits/stdc++.h>
#define INF 1000'000'000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct node{
	int sum, ans, pref, suff;
	node(int s, int a, int p, int sf):sum(s), ans(a), pref(p), suff(sf){}
	node(int val = 0){// single value
		sum = ans = pref = suff = val;
	}
};


node combine(node l, node r){
	int sum = l.sum + r.sum;
	int ans = max({l.ans, r.ans, l.suff + r.pref});
	int pref = max({l.pref, l.sum + r.pref});
	int suff = max(r.suff, r.sum + l.suff);
	return node(sum,ans,pref,suff);
}

vector < node > tree(200'000);
int n;
vector < int > a(50'000);


void build(int v = 1, int low = 0, int high = n-1){
	if(low == high){
		tree[v] = node(a[low]);
		return;
	}
	int mid = low + (high - low) / 2;
	build(v*2, low, mid), build(v*2+1, mid+1, high);
	tree[v] = combine(tree[v*2], tree[v*2+1]);
}


node query(int l, int r, int v = 1, int low = 0, int high = n-1){	
	if(l > r)
		return node(-INF);// invalid state could it happen? 
	else if(l <= low && r >= high)
		return tree[v];
	
	int mid = low + (high - low) / 2;
	auto q1 = query(l, min(r, mid), v*2, low , mid);
	auto q2 = query(max(mid+1, l), r, v*2+1, mid+1, high);
	if(q1.ans <= -INF)
		return q2;
	else if(q2.ans <= -INF)
		return q1;
	return combine(q1, q2);
}



int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> a[i];
	build();

	
	int q, l, r;
	cin >> q;
	
	while(q-- && cin >> l >> r){
		auto nd = query(l-1, r-1);
		cout << nd.ans << "\n";
	}
	
	return 0;
}
