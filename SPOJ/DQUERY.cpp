#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
#define INF 1000'000'000
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef tree<int , null_type,less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

constexpr int MXN = 30'005, MX_VAL = 1000'005;

struct seg_tree{
	int cnt;
	seg_tree *left, *right;
	seg_tree(){
		cnt = 0, left = right = this;
	}
	seg_tree(int c, seg_tree* l, seg_tree* r){
		cnt = c, left = l, right = r;
	}
	
	seg_tree* add(int idx, int val, int tl = 0, int tr = MX_VAL){
		if(tl > idx || tr < idx)
			return this;
		else if(tl == tr){
			return  new seg_tree(this -> cnt+val, left, right);
		}
		int mid = tl + (tr - tl) / 2;
		auto l = left -> add(idx, val, tl, mid);
		auto r = right -> add(idx, val, mid+1, tr);
		return new seg_tree(l -> cnt + r -> cnt, l, r);
	}
	int sum(int l, int r, int tl = 0, int tr = MX_VAL){
		//cout << "Cur cnt:" << cnt << " in range :" << tl << ", " << tr << endl;
		if(l > tr || r < tl)
			return 0;
		else if(l <= tl && r >= tr){
			return cnt;
		}
		int mid = tl + (tr - tl) / 2;
		return left -> sum(l, r, tl, mid) + right -> sum(l, r, mid+1, tr);
	}
};

int prev_occ[MX_VAL], a[MXN], n, m;
seg_tree* roots[MXN];
//int tmp_idx = 0;
//seg_tree* tmp[MXN];// for debug mode to ignore memory leaks
void build_seg_trees(){
	roots[0] = new seg_tree;
	for(int i = 1; i <= n;prev_occ[a[i]] = i, i++){
		roots[i] = roots[i-1] -> add(i, 1);
		if(prev_occ[a[i]] != 0){
			// debug
			//tmp[tmp_idx++] = roots[i];
			roots[i] = roots[i] -> add(prev_occ[a[i]], -1);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);//freopen("out", "w", stdout);
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	
	build_seg_trees();
	cin >> m;
	for(int i = 1, l, r; i <= m; i++){
		cin >> l >> r;
		cout << roots[r] -> sum(l, r) << "\n";
	}
	return 0;
}
