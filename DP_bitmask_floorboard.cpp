#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define INF INT_MAX

int W,H;

vector<vector<vector<vector<int>>>> dpI;
vector<vector<bool>> blocks;

int dp(bool b, int i, int j, int back){
	if(i == W){
		return dp(false,0,j+1,back);
	}
	if(j == H){
		return 0;
	}
	if(dpI[b][i][j][back] != -1){
		return dpI[b][i][j][back];
	}
	int ifNotBack = back & (((1 << W)-1) - (1<<i));
	if(blocks[i][j]){
		return dp(false,i+1,j,ifNotBack);
	}
	int res = INF;
	if(b){
		res = min(res,dp(true,i+1,j,ifNotBack));
	}
	else{
		res = min(res,1+dp(true,i+1,j,ifNotBack));
	}
	if(back & (1<<i)){
		res = min(res,dp(false,i+1,j,back));
	}
	else{
		res = min(res,1+dp(false,i+1,j,back + (1<<i)));
	}
	dpI[b][i][j][back] = res;
	return res;
}

int main(){
	cin>>W>>H;
	blocks.resize(W,vector<bool>(H,false));
	dpI.resize(2,vector<vector<vector<int>>>(W,vector<vector<int>>(H,vector<int>((1<<W),-1))));
	string line;
	for(int i = 0; i < H; ++i){
		cin>>line;
		for(int j = 0; j < W; ++j){
			blocks[j][i] = line[j] == '#';
		}
	}
	cout<<dp(0,0,0,0)<<endl;
	return 0;
}