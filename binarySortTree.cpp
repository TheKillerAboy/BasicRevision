#include <vector>
#include <iostream>

using namespace std;

void swap(vector<int>& arr, int a, int b){
	arr[a] = arr[a]^arr[b];
	arr[b] = arr[a]^arr[b];
	arr[a] = arr[a]^arr[b];
}

void insert(vector<int>& bt, int c){
	bt.push_back(c);
	int current = bt.size()-1;
	while(true){
		if(((current>>1)<<1) == current){
			if(bt[(current-1)/2] > bt[current]){
				swap(bt,(current-1)/2,current);
				current = (current-1)/2;
			}
		}
		else{
			if(bt[(current-1)/2] < bt[current]){
				swap(bt,(current-1)/2,current);
				current = (current-1)/2;
			}
		}
		break;
	}
};

void printVec(vector<int>& arr){
	for(size_t i = 0; i < arr.size(); i++){
		cout<< arr[i]<<' ';
	}
	cout<<endl;
}

int main(){
	vector<int> arr = {};
	insert(arr,7);
	insert(arr,9);
	insert(arr,4);
	printVec(arr);
}