#include<bits/stdc++.h>
#define INF 1000'000'000
using namespace std;
typedef  long long   ll;
typedef  unsigned long long ull;
typedef pair<int,int> pii;
int main (){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("in", "r", stdin);
	//freopen("out", "w", stdout);
	ll a, b;
	for(int tc = 1; cin >> a >> b && a|b; ++tc)
		cout << "Case " << tc << ": "<< (b*b - (b+1)*b/2) * ((a-1)*a/2) << "\n";
	
	return 0;
}
