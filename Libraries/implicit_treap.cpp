#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define INF 2000'000'000
using namespace std; 
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
template<typename T> using ordered_set = tree<T , null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
 
struct implicit_treap{
	struct node{
		int val, priority, sz;
		bool is_rev;
		node *l, *r;
		static node* empty;
		node(){// empty node
			val = 0, is_rev = 0, sz = 0, priority = -INF, l = r = this;
		}
		node(int v, node* lf = empty, node * rt = empty){
			val = v, sz = 1, is_rev = 0, priority = rand(), l = lf, r = rt;
		}
		void push_up(){
			if(this != empty)
				sz = 1 + l -> sz + r -> sz;
		}
		
		void push_down(){
			if(is_rev){				
				l -> reverse(), r -> reverse();
				is_rev = false;
			}
		}
		
		void reverse(){
			is_rev ^= 1;
			swap(l, r);
		}
		
	};
	node * root;
	
	implicit_treap(){
		root = node::empty;
	}
	
	void split(node* T, node *& l, node *& r, int lsz){
		if(T == node::empty){
			l = r = T;
			return;
		}
		T -> push_down();
		const int cur = T -> l -> sz + 1;
		if(cur <= lsz){
			split(T->r, T -> r, r, lsz - cur);
			l = T;
		}
		else{
			split(T -> l, l, T -> l, lsz);
			r = T;
		}
		T -> push_up();
	}
	void merge(node*& T, node *l, node * r){
		if(l == node::empty){
			T = r;
			return;
		}
		else if(r == node::empty){
			T = l;
			return;
		}
		l -> push_down(), r -> push_down();
		if(l -> priority > r -> priority){
			T = l;
			merge(l -> r, l -> r, r);
		}
		else{
			T = r;
			merge(r -> l, l, r -> l);
		}
		T -> push_up();
	}
	
	void insert(int idx, int val){// zero based index
		node* ins = new node(val), *ls, *gr;
		split(root, ls, gr, idx);
		merge(root, ls, ins);
		merge(root, root, gr);
	}
	
	void print(node * T){
		if(T == node:: empty)
			return;
		print(T->l);
		cout << T -> val << " ";
		print(T -> r);
	}
	
	void split_rng(node *& prv, node *& rng, node *& after, int l, int r){
		split(root, rng, after, r+1);
		split(rng, prv, rng, l);
	}

	void cyc_shift(node *& T){
		// get last item in r
		int sz = T -> sz;
		node * l, *r;
		split(T, l, r, sz-1);
		merge(T, r, l);
	}
	
	void cyc_shift(int l, int r){
		node *prv, *rng, *after;
		split_rng(prv, rng, after, l, r);
		cyc_shift(rng);
		merge(root, prv, rng);
		merge(root, root, after);
	}
	
	void reverse(int l, int r){
		node * prv, *rng, *after;
		split_rng(prv, rng, after, l, r);
		rng -> reverse();
		merge(root, prv, rng);
		merge(root, root, after);
	}
	
	
	int at(node * T, int idx){
		if(T == node::empty)
			exit(1);
		T -> push_down();
		int lsz = T -> l -> sz;
		if(idx < lsz)
			return at(T -> l, idx);
		else if(idx == lsz)
			return T -> val;
		return at(T -> r, idx - lsz - 1);
	}
	int at(int idx){	
		return at(root, idx);
	}
	
	int erase(node* &T, int idx){
		T -> push_down();
		if(T == node::empty){// never happens
			exit(1);
		}
		int lsz = T -> l -> sz, ans;
		if(idx < lsz)
			ans = erase(T -> l, idx);
		else if(idx == lsz){
			node * tmp = T;
			merge(T, T->l, T->r);
			ans = tmp -> val;
			delete tmp;
		}
		else{
			ans = erase(T->r, idx-lsz-1);
		}
		T -> push_up();
		return ans;
	}
	
	int erase(int idx){
		return erase(root, idx);
	}
	
};
implicit_treap::node* implicit_treap::node::empty = new implicit_treap::node;

implicit_treap tr;

 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);//freopen("out", "w", stdout);
	int n, q, m;
	cin >> n >> q >> m;
	for(int i = 0; i < n; i++){
		int cur;
		cin >> cur;
		tr.insert(i, cur);
	}
	
	while(q--){
		int type, l, r;
		cin >> type >> l >> r;
		l--, r--;
		if(type == 1){
			tr.cyc_shift(l, r);	
		}
		else if(type == 2){
			tr.reverse(l, r);
		}
	}
	for(int i = 0; i < m; i++){
		int pos;
		cin >> pos;
		cout << tr.at(pos-1) << " ";
	}
	
	return 0;
}
