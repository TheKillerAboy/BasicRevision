#include <iostream>
#include <array>
#include <memory>

using namespace std;

typedef array<int,2> Coor;

int distance(Coor a, Coor b){
  return abs(a[0]-b[0])+abs(a[1]-b[1]);
}


void printCoor(Coor a){
  cout<<'('<<a[0]<<", "<<a[1]<<')'<<endl;
}

class D2Node{
public:
  Coor value;
  unique_ptr<D2Node> leftC;
  unique_ptr<D2Node> rightC;
  D2Node(Coor loc){
    value = loc;
  }

  static void PUSH(unique_ptr<D2Node>& child, Coor loc,int cmpInd){
      if(!child){
        child = make_unique<D2Node>(loc);
      }
      else{
        child->push(loc,(cmpInd+1)%2);
      }
  }
  void push(Coor loc, int cmpInd){
    if(loc[cmpInd] >= value[cmpInd]){
      PUSH(rightC,loc,cmpInd);
    }
    else{
      PUSH(leftC,loc,cmpInd);
    }
  }
  void print(string taber){
    cout<<taber;
    printCoor(value);
    if(leftC){
      cout<<taber<<"L:"<<endl;
      leftC->print(taber+'\t');
    }
    if(rightC){
      cout<<taber<<"R:"<<endl;
      rightC->print(taber+'\t');
    }
  }
  int getMin(Coor loc, int cmpInd){
    int distanceS = distance(loc,value);
    if(loc[cmpInd] >= value[cmpInd]){
      if(!rightC){
        return distanceS;
      }
      else{
        return min(rightC->getMin(loc,(cmpInd+1)%2),distanceS);
      }
    }
    else{
      if(!leftC){
        return distanceS;
      }
      else{
        return min(leftC->getMin(loc,(cmpInd+1)%2),distanceS);
      }
    }
  }
};

class D2Tree{
public:
  unique_ptr<D2Node> root;
  D2Tree(){
    root = NULL;
  }
  void push(Coor loc){
    D2Node::PUSH(root,loc,1);
  }
  int getMin(Coor loc){
    return root->getMin(loc,0);
  }
  void print(){
    root->print("");
  }
};

int main(){
  D2Tree myTree;
  myTree.push(Coor{3,6});
  myTree.push(Coor{17,15});
  myTree.push(Coor{13,15});
  myTree.push(Coor{6,12});
  myTree.push(Coor{9,1});
  myTree.push(Coor{2,7});
  myTree.push(Coor{10,19});
  myTree.print();
  cout<<myTree.getMin(Coor{5,4})<<endl;
  return 0;
}
