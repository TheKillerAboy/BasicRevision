#include <stdlib.h>
#include <iostream>

void merge(int* arr,int* aux,int min,int mid, int max){
  int k = min;
  int l = mid+1;
  int c = min;

  while(k<=mid&&l<=max){
    if(arr[k]<arr[l]){
      aux[c++] = arr[k++];
    }
    else{
      aux[c++] = arr[l++];
    }
  }
  while(k<=mid){
    aux[c++] = arr[k++];
  }
  while(l<=max){
    aux[c++] = arr[l++];
  }
  for(int i = min; i <= max; i++){
    arr[i] = aux[i];
  }
}

void __mergeSort(int* arr,int* aux,int min, int max){
  if(min < max){
    int mid = (min+max)>>1;

    __mergeSort(arr,aux,min,mid);
    __mergeSort(arr,aux,mid+1,max);

    merge(arr,aux,min,mid,max);
  }
}

void mergeSort(int* arr,int size){
  int* aux = (int*) malloc(size*sizeof(int));
  for(int i = 0; i < size; i++){
    aux[i] = arr[i];
  }
  __mergeSort(arr,aux,0,size-1);
}

int main(int argc, char const *argv[]) {
  int arr[] = {1,2,6,3,4,88,43,22};
  mergeSort(arr,8);
  for(int i = 0; i < sizeof(arr)/sizeof(int); i++){
    std::cout<<arr[i]<<' ';
  }
  return 0;
}
