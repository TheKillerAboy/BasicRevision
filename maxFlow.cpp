#include <bits/stdc++.h>

using namespace std;

#define FOR(i_,a_) for(int i_=0;i_<a_;++i_)
#define FORR(i_,a_) for(int i_=a_-1;i_>=0;--i_)
#define FORI(i_,a_) for(int i_=1;i_<=a_;++i_)
#define FORA(i_,a_) for(auto i_:a_)
#define FOR1(i_,a_) for(int i_=1;i_<a_;++i_)
#define ll long long int
#define ull unsigned long long int
typedef pair<int,int> pii;
#define INF INT_MAX

int M,N,S,D;
int cut = 0;
vector<pii> DP;
vector<map<int,int>> connections;

pii dp(int n){
	if(DP[n] != pii{-1,-1}){
		return DP[n];
	}
	if(n == D){
		return {INF,-1};
	}
	pii out = {0,0};
	FORA(child , connections[n]){
		int best = min(dp(child.first).first,child.second);
		if(best > out.first){
			out = {best,child.first};
		}
	}
	DP[n] = out;
	return out;
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin>>N>>M;
	connections.resize(N);
	int a,b,c;
	FOR(i,M){
		cin>>a>>b>>c;
		connections[a][b] = c;
	}
	cin>>S>>D;
	DP.resize(N,pii{-1,-1});
	int current;
	while(connections[S][dp(S).second] > 0){
		cut += dp(S).first;
		current = S;
		while(current != D){
			connections[current][dp(current).second] -= dp(S).first;
			cout<<current<<' '<<dp(current).second<<' '<<connections[current][dp(current).second]<<'\n';
			current = dp(current).second;
		}
		DP = vector<pii>(N,pii{-1,-1});
	}
	cout<<cut;

	return 0;
}

/*
6
8
0 1 5
0 2 4
2 1 3
1 3 6
3 5 5
3 4 8
2 4 1
4 5 2
0 5
*/