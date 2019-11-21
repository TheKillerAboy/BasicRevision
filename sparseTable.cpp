#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> constructSparseTable(vector<int> arr, int n){
	vector<vector<int>> out(ceil(log2(n))+1, vector<int>(n,-1));
	for(int i = 0; i < n; i++){
		out[0][i] = arr[i];
	}
	for(int j = 1; j <= ceil(log2(n)); j++){
		int curPow = pow(2,j);
		for(int i = 0; i <= n -curPow + 1 ;i++){
			out[j][i] = min(out[j-1][i],out[j-1][i+curPow/2]);
		}
	}
	return out;
}

int getMin(vector<vector<int>>& st, int a, int b){
	int l = b-a+1;
	int k = floor(log2(l));
	return min(st[k][a],st[k][a+l-(int)pow(2,k)]);
}

int main(){
	vector<int> test = {1,2,-3,5,3,2,-5,7};
	auto st = constructSparseTable(test,test.size());
	cout<<getMin(st,0,0)<<endl;
}