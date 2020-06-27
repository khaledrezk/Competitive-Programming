#include<bits/stdc++.h>
#define INF 1000'000'000
#define MOD 3000'000'019
#define P  1009
using namespace std;
typedef  long long   ll;
typedef  unsigned long long   ull;

ll power(ll b, ll p){	
	if(p == 0)
		return 1;
	ll sq = power(b, p/2);
	return (sq * sq % MOD * (p & 1 ? b : 1)) % MOD;
}

int main (){
	//ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("in", "r", stdin);
	int n;
	string pat;
	ll p_inv = power(P, MOD-2);
	while(cin >> n >> pat){
		//getline(cin, s),getline(cin, s);
		getchar();// gets '\n'
		
		ll h = 0, p_pow = 1;
		for(char c : pat)
			h = (h + c * p_pow) % MOD, p_pow = (p_pow * P) % MOD;
		ll h2 = 0;
		p_pow = 1;
		char c;
		list<char> s;
		for(int i = 0; (c = getchar()) != '\n'; i++){//max pow = n-1
			s.push_back(c);
			//h2 = (h2 + s[i] * p_pow) % MOD;
			if(i >= n){// remove first char
				h2 -= s.front(), h2 *= p_inv, s.pop_front();
			}
			h2 += c * p_pow;
			h2 = (h2 % MOD + MOD) % MOD;
			if(i >= n-1 && h == h2)// check current indx
				cout << i - n + 1<< "\n";
				
			if(i + 1 < n)
				p_pow = (p_pow * P) % MOD;
		}
		cout << '\n';
	}
	return 0;
}
