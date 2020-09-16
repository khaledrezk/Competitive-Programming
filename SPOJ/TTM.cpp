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
constexpr int MXN = 1e5 + 5;

int nxt_node= 0;
//struct seg_tree;
//seg_tree* tmp[MXN*30];

struct seg_tree{
	ll sum, add;
	seg_tree *left, *right;
	seg_tree(){
		sum = 0, add = 0;
		left = right = this;
		//tmp[nxt_node++] = this;
	}
	seg_tree(ll s, ll a, seg_tree* l, seg_tree* r){
		sum = s, add = a, left = l, right = r;
		//tmp[nxt_node++] = this;
	}
	
	seg_tree* range_add(int l, int r, ll val, int tl = 0, int tr = MXN){
		if(l > tr || r < tl)
			return this;
		else if(l <= tl && r >= tr){
			//cout << "Adding at range:" << tl << ", " << tr << " new sum:" << sum << " + " <<  (tr - tl + 1) << " * " <<  val << endl;
			return new seg_tree(sum + (tr - tl + 1)* val, add + val, left, right);
		}
		int mid = tl + (tr - tl) / 2;
		auto lf = left -> range_add(l, r, val, tl, mid);
		auto rt = right -> range_add(l, r, val, mid+1, tr);
		return new seg_tree(lf -> sum + rt -> sum + add*(tr-tl+1), add, lf, rt);
	}
	
	ll range_sum(int l, int r, ll added = 0, int tl = 0, int tr = MXN){
		if(tl > r || tr < l)
			return 0;
		//cout << "current range :" << tl << ", " << tr << " added:" << added << " total sum:" << sum << endl;
		if(l <= tl && r >= tr){
		//	cout << "range [" << tl <<", " << tr << "] included return:" << sum << " + " << added << " * " << (tr - tl + 1) << endl;
			return sum + added * (tr - tl + 1);
		}
		int mid = tl + (tr - tl) / 2;
		added += add;
		ll q1 = left -> range_sum(l,r,added, tl, mid);
		ll q2 = right -> range_sum(l,r,added, mid+1, tr);
		return q1 + q2;
	}
};

int n, m, a[MXN], cur_timer = 0;
seg_tree* roots[MXN];

void build(){
	roots[0] = new seg_tree;
	for(int i = 1; i <= n; i++)
		roots[0] = roots[0] -> range_add(i, i, a[i]);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("int", "r", stdin);//freopen("out", "w", stdout);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	build();
	while(m--){
		char c;
		int l, r, d, t;
		cin >> c;
		if(c == 'B'){
			cin >> t;
			cur_timer = t;
		}
		else if(c == 'Q'){
			cin >> l >> r;
			cout << roots[cur_timer] -> range_sum(l, r) << "\n";
			
		}
		else if(c == 'H'){
			cin >> l >> r >> t;
			cout << roots[t] -> range_sum(l, r) << "\n";
		}
		else if(c == 'C'){
			cin >> l >> r >> d;
			roots[cur_timer + 1] = roots[cur_timer] -> range_add(l, r, d);
			cur_timer++;
			/*cout << "Printing all version:" << endl;
			for(int vr = 0; vr <= cur_timer; vr++){
				cout << "version :" << vr << " = [";
				for(int i = 1; i <= n; i++)
					cout << roots[vr] ->range_sum(i,i) <<", ";
				cout << "]\n";
			}
			cout << endl << endl;*/
		}
		
		//cout << flush;
	}
	return 0;
}	
