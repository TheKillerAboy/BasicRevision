#include <bits/stdc++.h>

using namespace std;

#define FOR(i_,a_) for(int i_=0;i_<a_;++i_)
#define FORR(i_,a_) for(int i_=a_-1;i_>=0;--i_)
#define FORI(i_,a_) for(int i_=1;i_<=a_;++i_)
#define FORA(i_,a_) for(auto i_:a_)
#define ll long long int
#define INF INT_MAX/2

string A,B;

vector<vector<int>> DP;

int dp(int x, int y);

int getdp(int x, int y){
	if(x >= A.size() && y>=B.size()){
		return 0;
	}
	else if(x >= A.size() || y>=B.size()){
		return INF;
	}
	if(DP[x][y] == -1){
		DP[x][y] = dp(x,y);
	}
	return DP[x][y];
}

int dp(int x, int y){
	if(A[x] == B[y]){
		return getdp(x+1,y+1);
	}
	int out = min(getdp(x+1,y+1),getdp(x+1,y));
	return min(out,getdp(x,y+1))+1;
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin>>A>>B;
	DP.resize(A.size(),vector<int>(B.size(),-1));
	cout<<getdp(0,0);
	return 0;
}