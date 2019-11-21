#include <bits/stdc++.h>

using namespace std;

#define FOR(i_,a_) for(int i_=0;i_<a_;++i_)
#define FORR(i_,a_) for(int i_=a_-1;i_>=0;--i_)
#define FORI(i_,a_) for(int i_=1;i_<=a_;++i_)
#define FOR1(i_,a_) for(int i_=1;i_<a_;++i_)
#define FORA(i_,a_) for(auto i_:a_)
#define ll long long int

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int N;
	cin>>N;
	vector<int> arr(N);
	int SUM = 0;
	FOR(i,N){
		cin>>arr[i];
		SUM += arr[i];
	}
	vector<vector<int>> dp(N+1,vector<int>(SUM+1,false));
	FOR(i,N){
		dp[i][0] = 1;
	}
	FOR1(i,N+1){
		FOR1(j,SUM+1){
			dp[i][j] = dp[i-1][j];
			if(arr[i-1] <= j){
				dp[i][j] = dp[i][j] | dp[i-1][j-arr[i-1]];
			}
		}
	}
	for(int j = SUM/2; j>=0; j--){
		if(dp[N][j]){
			cout<<SUM-2*j;
			break;
		}
	}


	return 0;
}