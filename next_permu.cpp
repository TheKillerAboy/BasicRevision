#include <iostream>

using namespace std;

void swap(int* arr, int a, int b){
	if(a==b){
		return;
	}
	arr[a] = arr[a]^arr[b];
	arr[b] = arr[a]^arr[b];
	arr[a] = arr[a]^arr[b];
}

bool next_permu(int* arr, int n){
	int l = n-1;
	for(int i = n-2; i >= 0; i--){
		if(arr[i] > arr[i+1]){
			l--;
		}
		else{
			break;
		}
	}
	if(l==0){
		return false;
	}
	int swa = -1;
	for(int i = n-1; i >= l; i--){
		if(arr[i] > arr[l-1]){
			swa = i;
			break;
		}
	}
	swap(arr,l-1,swa);
	for(int i = l; i <= (n-1+l)>>1; i++){
		swap(arr,i,n-1+l-i);
	}
	return true;
}

int main(){
	int arr[] = {3,2,1};
	next_permu(arr,3);
	for(int i = 0; i < 3; i++){
		cout<<arr[i]<<' ';
	}
	return 0;
}