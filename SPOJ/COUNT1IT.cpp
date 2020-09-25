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
template<typename T> using ordered_set = tree<T , null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct treap{
	struct node{
		int val, priority, freq, sz;
		node *left, *right;
		node(){// init empty node only
			val = freq = sz = 0; 
			priority = -INF, left = right = this;
		}
		node(int v, node* l, node* r){
			val = v, freq = 1;
			priority = rand();
			left = l;
			right = r;
		}
		void push_up(){
			sz = left -> sz + right -> sz + freq;	
		}
	};
	
	node *root, *empty;
	treap(){
		empty = new node;
		root = empty;
	}
	
	void split(node *cur_root, const int val, node *&l, node *&r){
		if(cur_root == empty)
			l = r = empty;
		else if(cur_root -> val <= val){
			split(cur_root -> right, val, cur_root -> right, r);
			l = cur_root;
			l -> push_up();
		}
		else{
			split(cur_root -> left, val, l, cur_root -> left);
			r = cur_root;
			r -> push_up();
		}
	}
	void merge(node *&ret, node *t1, node* t2){
		if(t1 == empty){
			ret = t2;
		}
		else if(t2 == empty){
			ret = t1;
		}
		else if(t1 -> priority > t2 -> priority){// t1 on top
			merge(t1 -> right, t1 -> right, t2);
			ret = t1;
		}
		else {
			merge(t2 -> left, t1, t2 -> left);
			ret = t2;
		}
		ret -> push_up();
	}
	
	void insert(node *&cur_root, node* nd){
		if(cur_root == empty)
			cur_root = nd;
		else if(nd -> priority > cur_root -> priority){
			// nd should be the new root
			split(cur_root, nd->val,  nd -> left, nd -> right);
			cur_root = nd;
		}
		else if(nd -> val <= cur_root -> val){// insert left
			insert(cur_root -> left, nd);
		}
		else {
			insert(cur_root -> right, nd);
		}
		cur_root -> push_up();
	}
	void insert(int val){
		if(add1(root, val)){
			return;
		}
		insert(root, new node(val, empty, empty));
	}
	
	bool add1(node* cur_root, int val){
		bool ret = 0;
		if(cur_root == empty)
			return false;
		else if(cur_root -> val == val){
			cur_root -> freq++;
			ret = 1;
		}
		else if(val < cur_root -> val){
			ret = add1(cur_root -> left, val);
		}
		else{
			ret = add1(cur_root -> right, val);
		}
		cur_root -> push_up();
		return ret;
	}
	
	int cnt_leq(node* cur_root, int val){// less than or equal
		if(cur_root == empty)
			return 0;
		else if(cur_root -> val <= val){
			return cur_root -> freq + cur_root -> left -> sz + cnt_leq(cur_root -> right, val);
		}
		return cnt_leq(cur_root -> left, val);
	}
	
	int cnt_leq(int val){
		return cnt_leq(root, val);
	}
	int kth(node* cur_root, int k){	
		if(cur_root -> left -> sz >= k)
			return kth(cur_root -> left, k);
		k -= cur_root -> left -> sz;
		if(k <= cur_root -> freq)
			return cur_root -> val;
		k -= cur_root -> freq;
		return kth(cur_root -> right, k);
	}
	
	int kth(int k){
		if(root -> sz < k)
			return INT_MAX;
		return kth(root, k);
	}
	
	node* find(node * cur_root, int val){
		if(cur_root == empty || cur_root -> val == val)
			return cur_root;
		if(val < cur_root -> val)
			return find(cur_root -> left, val);
		return find(cur_root -> right, val);
	}
	int cnt(int val){
		return find(root, val) -> freq;
	}
	
};

treap st;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);//freopen("out", "w", stdout);
	int n, q;
	cin >> n >> q;
	for(int i = 0, val; i < n && cin >> val; i++){
		st.insert(val);
	}
	for(int i = 0, t, x; i < q && cin >> t >> x; i++){
		if(t == 1){
			int leq = st.cnt_leq(x);
			st.insert(x+leq);
		}
		else if(t == 2){
			cout << st.cnt_leq(x) << "\n";
		}
		else if(t == 3){
			auto ans = st.kth(x);
			if(ans == INT_MAX)
				cout << "invalid\n";
			else
				cout << ans << "\n";
		}
		//cout << flush;
	}
	return 0;
}
