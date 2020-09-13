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
typedef tree<pair<int,int> , null_type,greater<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

struct node{
	const int cnt;
	node *left, * right;
	node(): cnt(0){// for empty node
		left = right = this;
	}
	node(int val, node* l,node* r): cnt(val){
		left = l, right = r;
	}
	
	node* insert(int val, int tl = -INF, int tr = INF){
		if(val < tl || val > tr){
			return this;
		}
		else if(tl == val && tr == val){
			return new node(this->cnt+1, this -> left, this -> right);	
		}
		int mid = tl + (tr - tl) / 2;
		auto cur_l = left  -> insert(val, tl, mid);
		auto cur_r = right -> insert(val, mid+1, tr);
		return new node(cur_l -> cnt + cur_r -> cnt, cur_l, cur_r);
	}
};

int kth(int k, node*add, node* rem, int tl = -INF, int tr = INF){
	if(tl == tr){
		return tl;// assuming k-th always exist
	}
	int left_cnt = add->left->cnt - rem ->left-> cnt;
	int mid = tl + (tr - tl) / 2;
	if(left_cnt >= k){
		return kth(k, add -> left, rem -> left, tl, mid);
	}
	return kth(k-left_cnt, add -> right, rem -> right, mid+1, tr);
}

constexpr int MXN = 100'005;
int n, m;
node* seg_trees[MXN];
int a[MXN];

void build_trees(){
	//seg_trees[0] = node :: empty;
	seg_trees[0] = new node;
	for(int i = 1; i <= n; i++){
		seg_trees[i] = seg_trees[i-1]->insert(a[i]);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);//freopen("out", "w", stdout);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	build_trees();
	for(int l, r, k; m-- && cin >> l >> r >> k; ){
		cout << kth(k, seg_trees[r], seg_trees[l-1]) << "\n";	
	}
	return 0;
}
