#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int,int> Coor;
set<Coor> points;

bool isLeftFrom(Coor last, Coor last2, Coor last3){
	int U1,U2,D1,D2;
	D1 = abs(last.first - last2.first);
	D2 = abs(last2.first - last3.first);
	U1 = abs(last.second - last2.second);
	U2 = abs(last2.second - last3.second);
	return D2*U1 > D1*U2;
}

int main(){
	int N;
	cin>>N;
	int x,y;
	for(int i = 0; i < N; i++){
		cin>>x>>y;
		points.insert({x,y});
	}
	vector<Coor> upper_hull;
	for(Coor loc: points){
		while(upper_hull.size()>=2 && isLeftFrom(loc,upper_hull.back(),upper_hull[upper_hull.size()-2])){
			upper_hull.pop_back();
		}
		upper_hull.push_back(loc);
	}
	for(Coor ele : upper_hull){
		cout<<ele.first+", "<<ele.second<<' '<<endl;
	}
}

/*
8
0 1
1 0
2 0
3 1
3 2
2 3
1 3
0 2
*/