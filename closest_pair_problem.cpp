#include <set>
#include <iostream>
#include <utility>
#include <climits>
#include <cmath>

using namespace std;

#define ll long long int
#define lld long double
#define INF LLONG_MAX
typedef pair<ll,ll> Coor;

set<Coor> points;
void CoorLog(Coor a){
	cout<<"( "<<a.first<<", "<<a.second<<") ";
}

lld distance(Coor a, Coor b){
	return sqrt(pow(a.first-b.first,2)+pow(a.second-b.second,2));
}

int main(){
	lld d = INF;
	pair<Coor,Coor> dCoors;
	ll N;
	cin>>N;
	ll x,y;
	for(ll i = 0; i < N ;i++){
		cin>>x>>y;
		points.insert({x,y});
	}
	for(auto it = points.begin(); it != points.end(); it++){
		auto itC = it;
		while(itC != points.begin()){
			advance(itC,-1);
			if((*it).first - (*itC).first<=d){
				if(abs((*it).second - (*itC).second) <= d){
					if(distance(*it,*itC) < d){
						d = distance(*it,*itC);
						dCoors = {*it,*itC};
					}
				}
			}
			else{
				break;
			}
		}
	}
	CoorLog(dCoors.first);
	CoorLog(dCoors.second);
}