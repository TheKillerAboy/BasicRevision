#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

#define ll long long int

vector<pair<ll,bool>> times;

int main(){
	ll n;
	cin>>n;
	times.resize(2*n);
	ll a,b;
	for(ll i = 0; i < n; i++){
		cin>>a>>b;
		times[2*i] = {a,false};
		times[2*i+1] = {b,true};
	}
	sort(times.begin(),times.end());
	ll counter = 0;
	ll maxC = 0;
	for(ll i = 0; i < 2*n; i++){
		if(times[i].second){
			counter--;
		}
		else{
			counter++;
		}
		maxC = max(maxC,counter);
	}
	cout<<maxC<<endl;

	return 0;
}