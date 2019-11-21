#include <iostream>

using namespace std;

void updateBIT(int* BITree,int size, int index, int value){
  index = index + 1;
  while(index <= size){
    BITree[index] += value;
    index+=index&(-index);//get next node to update;
  }
}

int* constructBIT(int* arr, int size){
  int* BITree = new int[size+1];
  for(int i = 1; i <= size;i++){
    BITree[i]=0;
  }
  for(int i = 0; i < size;i++){
    updateBIT(BITree,size,i,arr[i]);
  }
  return BITree;
}

int getSum(int* BITree, int size, int index){
  int sum = 0;
  index = index + 1;
  while(index > 0){
    sum+=BITree[index];
    index-=index&(-index);//get parent of current node
  }
  return sum;
}

/*
  Think about it as such, as you trivers from the index+1 node to the root, you get
  the sum of 0..index; Meaning that pathway is a shortcut to the awnser you are
  looking for
*/

int main(int argc, char const *argv[]) {
  cout<<1<<' '<<getParent(1)<<endl;
  return 0;
}
