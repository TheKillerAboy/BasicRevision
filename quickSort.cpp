#include <iostream>

void swap(int* arr, int a, int b){
  int a_copy = arr[a];
  arr[a] = arr[b];
  arr[b] = a_copy;
}

void quickSort(int* arr,int min, int max){
  if(min < max){
    int pivit = max;
    int k = min;
    while(k<max){
      if(k == pivit){
        k++;
      }
      if(k < pivit){
        if(arr[k]>arr[pivit]){
          swap(arr,k,pivit);
          pivit = k;
        }
      }
      else if(k > pivit){
        if(arr[k]<arr[pivit]){
          swap(arr,k,pivit);
          pivit = k;
        }
      }
      k++;
    }
    quickSort(arr,min,pivit-1);
    quickSort(arr,pivit+1,max);
  }
}

int main(int argc, char const *argv[]) {
  int arr[] = {1,2,6,3,4,88,43,22};
  quickSort(arr,0,7);
  for(int i = 0; i < 8; i++){
    std::cout<<arr[i]<<' ';
  }
  return 0;
}
