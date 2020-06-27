#include <bits/stdc++.h>
 
using namespace std;
vector < string > game(3);

bool winning_position(vector < string > g){
	bool ret = g[0][0] != '.' && g[0][1] == g[0][0] && g[0][2] == g[0][0];
	ret |=	   g[1][0] != '.' && g[1][1] == g[1][0] && g[1][2] == g[1][0];
	ret |= 	   g[2][0] != '.' && g[2][1] == g[2][0] && g[2][2] == g[2][0];
	// all rows checked now check columns
	ret |= 	   g[0][0] != '.' && g[1][0] == g[0][0] && g[2][0] == g[0][0];
	ret |=     g[0][1] != '.' && g[1][1] == g[0][1] && g[2][1] == g[0][1];
	ret |=     g[0][2] != '.' && g[1][2] == g[0][2] && g[2][2] == g[0][2];
	// all columns checked
	ret |=     g[0][0] != '.' && g[1][1] == g[0][0] && g[2][2] == g[0][0];
	ret |=     g[0][2] != '.' && g[1][1] == g[0][2] && g[2][0] == g[0][2];
	return ret;
}

bool bfs(){
	vector < string > empty = { "...", "..." , "..."};
	queue < vector < string > > q; 
	set < vector < string > > vis;
	q.push(empty), vis.insert(empty);
	bool player = 0; // 0 => x, 1 => y
	char player_char[] = {'X', 'O'};
	for(unsigned int sz = q.size(); !q.empty() ; sz = q.size(), player = !player){
		while(sz--){
			auto v = q.front(); q.pop();
			if(v == game){
				if(winning_position(v))
					return true; // found valid path to win
				for(string s : v)
					for(char c : s)
						if(c == '.')
							return false;
				return true;
			}
			else if(winning_position(v))
				continue;
			
			char c = player_char[player];
			for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++)
					if(game[i][j] == c && v[i][j] =='.'){ // valid next move
						auto u = v;
						u[i][j] = c;
						if(vis.find(u) == vis.end())
							vis.insert(u), q.push(u);
					}
		}
	}
	return false;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.in", "r", stdin);
	string row;
	while(cin >> row && row != "end"){
		game[0] = string(row.begin(), row.begin() + 3);
		game[1] = string(row.begin()+3, row.begin()+ 6);
		game[2] = string(row.begin()+6, row.end());
		//print game
		//cout << game[0] << endl << game[1] << endl << game[2] << endl << endl;
		cout << (bfs() ? "valid" : "invalid") << endl;
	}
	return 0;
}
