#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
#define INF 2000'000'000

#define ALPHA 26 // count of chars in alphabet

using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef tree<int, null_type,less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

/// Aho corasick with array based implemenation of Trie
struct Trie{
	struct node{
		int child[ALPHA], nxt_lnk[ALPHA];// children query for failure to each letter
		vector < int > pat_id;
		int fail;
		
		node(){// -1 == nullptr
			fail = 0;
			memset(child, -1, ALPHA * sizeof(int));
			memset(nxt_lnk,0, ALPHA * sizeof(int));// initially all links to root
		}
	};
	
	vector < node > T;
	Trie(int MX_SIZE = 1){// optional initial size to replace memory reallocations.
		T.reserve(MX_SIZE);
		T.push_back(node());
	}
	
	void insert(string & s, int id){
		int cur = 0;
		for(char c : s){
			int idx = c-'a';
			if(T[cur].child[idx] == -1){
				T[cur].child[idx] = T.size();
				T.push_back(node());
			}
			cur = T[cur].child[idx];
		}
		T[cur].pat_id.push_back(id);
	}
	
	void build_failure_links(){
		queue < int > q;
		q.push(0);
		while(!q.empty()){
			int v = q.front(); q.pop();
			for(int i = 0; i < ALPHA; i++){// initial value before processing children
				T[v].nxt_lnk[i] = T[T[v].fail].nxt_lnk[i];
			}
			
			for(int i = 0; i < ALPHA; i++){
				int u = T[v].child[i];
				if(u != -1){// check if any failure link has letter i
					T[u].fail = T[v].nxt_lnk[i], q.push(u);
					T[v].nxt_lnk[i] = u;//failure to child is a better value
					auto & vec = T[T[u].fail].pat_id;
					copy(vec.begin(), vec.end(), back_inserter(T[u].pat_id));
				}
			}
		}
	}
	
	void match(const string & s, vector < pair<int, int> > &ids){//{patId, index of last letter of match in s.
		int cur = 0;
		for(int i = 0; i < (int)s.size(); i++){
			cur = T[cur].nxt_lnk[s[i]-'a'];
			for(auto & id : T[cur].pat_id){
				ids.push_back({id,i});
			}
		}
	}
	
};

