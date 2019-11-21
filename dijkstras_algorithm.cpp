#include <queue>
#include <iostream>
#include <set>
#include <array>
#include <map>

using namespace std;

#define INF 999999

typedef pair<int,int> Coor;
#define X first
#define Y second
struct distanceCoor{
  Coor loc;
  Coor parent;
  int distance;
};

auto cmp = [](distanceCoor* a, distanceCoor* b){return a->distance<b->distance;};

set<distanceCoor*,decltype(cmp)> theQueue(cmp);
set<Coor> searchedSet;
map<Coor,distanceCoor*> mappedDC;

array<Coor,4> OFFSETS = array<Coor,4>{Coor{1,0},Coor{-1,0},Coor{0,-1},Coor{0,1}};

vector<vector<char>> mapC;

int N,M;

Coor START,END;

char getLoc(Coor a){
  return mapC[a.Y][a.X];
}

bool inBound(Coor a){
  return 0<=a.X &&a.X <M && 0<=a.Y && a.Y<N;
}

Coor addCoors(Coor a, Coor b){
  return Coor{a.X+b.X,a.Y+b.Y};
}

vector<Coor> getConnected(Coor a){
  vector<Coor> out;
  out.reserve(4);
  for(auto offset : OFFSETS){
    Coor newLoc = addCoors(offset,a);
    if(inBound(newLoc) && getLoc(newLoc) != '#'){
      out.push_back(newLoc);
    }
  }
  return out;
}

int shortestPath(){
  distanceCoor* currentDC = *theQueue.begin();
  while(currentDC->loc != END){
    theQueue.erase(currentDC);
    searchedSet.insert(currentDC->loc);
    for(auto nextLoc : getConnected(currentDC->loc)){
      if(searchedSet.find(nextLoc) == searchedSet.end()){
        if(mappedDC.find(nextLoc) == mappedDC.end()){
          mappedDC[nextLoc] = new distanceCoor{nextLoc,currentDC->loc,currentDC->distance+1};
        }
        else{
          distanceCoor* nextLocDC = mappedDC[nextLoc];
          if(currentDC->distance+1 < nextLocDC->distance){
            theQueue.erase(nextLocDC);
            nextLocDC->parent = currentDC->loc;
            nextLocDC->distance = currentDC->distance+1;
            theQueue.insert(nextLocDC);
          }
        }
      }
    }
    delete currentDC;
    currentDC = *theQueue.begin();
  }
  return currentDC->distance;
}

int main(){
  string mapLiteral = "*S*****####***#******E**";
  N = 4;
  M = 6;
  mapC.resize(N);
  for(int i = 0; i < N; i++){
    mapC[i].resize(M);
    for(int j = 0; j < M; j++){
      mapC[i][j] = mapLiteral[i*N+j];
      if(mapC[i][j] == 'S'){
        START = Coor{j,i};
      }
      else if(mapC[i][j] == 'E'){
        END = Coor{j,i};
      }
    }
  }
  mappedDC[START] = new distanceCoor{START,Coor{-1,-1},0};
  theQueue.insert(mappedDC[START]);
  cout<<shortestPath()<<endl;
  return 0;
}
