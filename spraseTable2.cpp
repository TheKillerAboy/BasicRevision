#include <iostream>
#include <vector>
#include <cmath>



int POW2(int k){
	return (1<<k);
}

using namespace std;
vector<vector<int>> creatSparseTable(vector<int>& arr){
	int n = arr.size();
	vector<vector<int>> out(ceil(log2(n)),vector<int>(n,0));
	for(int i = 0; i < n; i++){
		out[0][i] = arr[i];
	}
	for(int j = 1; j < out.size(); j++){
		int pow2 = POW2(j);
		for(int i = 0; i < n - pow2 + 1; i++){
			out[j][i] = min(out[j-1][i],out[j-1][i+pow2/2]);
		}
	}
	return out;
}


int getMin(vector<vector<int>>& st, int a, int b){
	int l = b-a+1;
	int k = floor(log2(l));
	return min(st[k][a],st[k][a+l-POW2(k)]);
}

int main(){
	vector<int> arr = {2, 3, 5, 4, 6, 8};
	vector<vector<int>> st = creatSparseTable(arr);
	cout<<getMin(st,0,2)<<endl;
	return 0;
}