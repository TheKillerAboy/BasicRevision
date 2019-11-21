#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <utility>

using namespace std;

struct State{
	vector<State*> connected;
	int GrundyNum;

	State(){
		GrundyNum = -1;
	}

	void calculateGundyNum(){
		if(GrundyNum != -1){
			return;
		}
		set<int> nums;
		for(auto con : connected){
			con->calculateGundyNum();
			nums.insert(con->GrundyNum);
		}
		GrundyNum = 0;
		while(nums.find(GrundyNum) != nums.end()){
			GrundyNum++;
		}
	}
};

typedef pair<int,int> Coor;

void connectStates(map<Coor,State*>& states, Coor curLoc){
	for(int i = curLoc.first - 1; i >= 1; i--){
		Coor newLoc = {i,curLoc.second};
		if(states[newLoc] != NULL){
			connectStates(states,newLoc);
			states[curLoc]->connected.push_back(states[newLoc]);
		}
		else{
			break;
		}
	}
	for(int i = curLoc.second - 1; i >= 1; i--){
		Coor newLoc = {curLoc.first,i};
		if(states[newLoc] != NULL){
			connectStates(states,newLoc);
			states[curLoc]->connected.push_back(states[newLoc]);
		}
		else{
			break;
		}
	}
}

int main(){
	vector<string> grid{
		"..#..",
		"#...#",
		"..#..",
		"#....",
		".....",
	};
	Coor start = {5,5};
	map<Coor,State*> states;
	for(size_t i = 0; i < grid.size(); i++){
		for(size_t j = 0; j < grid[i].length();j++){
			states[{j+1,i+1}] = grid[i][j] == '#' ? NULL : new State();
		}
	}
	connectStates(states,start);
	states[start]->calculateGundyNum();
	for(auto keyValue : states){
		if(keyValue.second != NULL){
			cout<<keyValue.first.first<<' '<<keyValue.first.second<<' '<<keyValue.second->GrundyNum<<endl;
		}
	}
}