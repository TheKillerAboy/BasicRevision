#include <iostream>

using namespace std;

void swapIndexs(int* arr, int a, int b){
    int swap = arr[a];
    arr[a] = arr[b];
    arr[b] = swap;
}

void heapifyDown(int* hp, int size, int index){
  if(2*index+2<size){
    if(hp[2*index+2]>hp[2*index+1]){
      if(hp[index]<hp[2*index+2]){
        swapIndexs(hp,index,2*index+2);
        heapifyDown(hp,size,2*index+2);
        return;
      }
    }else{
      if(hp[index]<hp[2*index+1]){
        swapIndexs(hp,index,2*index+1);
        heapifyDown(hp,size,2*index+1);
        return;
      }
    }
  }
  else if(2*index+1<size){
      if(hp[index]<hp[2*index+1]){
        swapIndexs(hp,index,2*index+1);
        heapifyDown(hp,size,2*index+1);
        return;
      }
  }
}

void heapifyUp(int* hp, int index){
  if((index-1)/2 >= 0){
    if(hp[(index-1)/2]<hp[index]){
      swapIndexs(hp,index,(index-1)/2);
      heapifyUp(hp,(index-1)/2);
    }
  }
}

void heapInsert(int* hp,int newIndex, int value){
  hp[newIndex] = value;
  heapifyUp(hp,newIndex);
}

int heapPop(int* hp,int size){
  swapIndexs(hp,0,size-1);
  heapifyDown(hp,size-1,0);
  int out = hp[size-1];
  hp[size-1] = -1;
  return out;
}

int main(int argc, char const *argv[]) {
  int* hp = new int[100];
  for(int i = 0; i < 100;i++){
    heapInsert(hp,i,i);
  }
  for(int i = 0; i < 100;i++){
    printf("%i\n", heapPop(hp,100-i));
  }
  return 0;
}
