#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
#define INF 2000'000'000

using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef tree<int, null_type,less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


// aho Corasick implementation
int cnt = 0;
struct Trie{
	map < char, Trie* > next, fail_queries;// queries for nodes failing on me
	vector < int > str_id;
	Trie* fail;
	Trie(){
		fail = NULL;
	}
	~Trie(){
		destroy();
	}
	
	void destroy(){
		for(auto & p : next){
			if(p.second){	
				p.second -> destroy();
				delete p. second;
			}
			p.second = NULL;
			
		}
	}
	
	void insert_str(string & s, int id){
		auto cur = this;
		for(char c : s){
			if(cur -> next.find(c) == cur -> next.end())
				cur -> next[c] = new Trie;
			cur = cur -> next[c];
		}
		cur -> str_id.push_back(id);
	}
	
	void build_failure_links(){
		queue < Trie* > q;
		q.push(this);
	
		while(!q.empty()){
			auto v = q.front(); q.pop();
			if(!v -> fail)
				v -> fail = this;
			for(auto & p : v->fail -> fail_queries){
				if(p.second)
					v->fail_queries[p.first] = p.second;	
			}
			for(auto & p : v -> next){
				auto u = p.second;
				auto ch = p.first;
				u -> fail = v -> fail_queries[ch];
				if(! u -> fail)
					u -> fail = this;
				
				
				for(int id : u -> fail ->  str_id)
					u -> str_id .push_back(id);
				q.push(u);
			}
			for(auto& p : v-> next){// if have next add it and remove from fail
				if(p.second){
					v->fail_queries[p.first] = p.second;	
				}
			}
		}
	}
	
	void match_string(string & s, vector < bool > & ids){
		auto cur = this;
		for(char c : s){
			cur = cur -> fail_queries[c];
			if(!cur)
				cur = this;
			for(int id : cur -> str_id)
				ids[id] = 1;
		}
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("in", "r", stdin);
	//freopen("out", "w", stdout);
	int t;
	cin >> t;
	while(t--){
		string s;
		int n;
		cin >> s >> n;
		
		vector < string > pat(n);
		for(string & cur : pat)
			cin >> cur;
		
		Trie tr;
		
		for(int i = 0; i < n; i++){
			tr.insert_str(pat[i], i);
		}
		tr.build_failure_links();
		vector < bool > ans(n);
		tr.match_string(s, ans);
		for(auto i : ans)// Y if i-th pattern is found in
			cout << (i ? "y" : "n") << "\n";
		//cout << flush;
	}
	return 0;
}
