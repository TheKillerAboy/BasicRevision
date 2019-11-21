#include <iostream>

using namespace std;

int ceilLog2(int n){
  int out = 0;
  float N = (float)n;
  while(N > 1){
    out ++;
    N/=2;
  }
  return out;
}

int power2(int a){
  int out = 1;
  for( int i = 0; i < a; i++){
    out*=2;
  }
  return out;
}

int MIN(int a,int b){
  if(a == -1){
    return b;
  }
  else if(b==-1){
    return a;
  }
  if(a>b){
    return b;
  }
  return a;
}

int MAX(int a,int b){
  if(a == -1){
    return b;
  }
  else if(b==-1){
    return a;
  }
  if(a<b){
    return b;
  }
  return a;
}

void fillSegmentTree(int* arr,int* st, int l, int r, int ni){
  if(l<=r){
    if(l!=r){
      int mid = (l+r)>>1;
      fillSegmentTree(arr,st,l,mid,2*ni + 1);
      fillSegmentTree(arr,st,mid+1,r,2*ni + 2);
      st[ni] = MIN(st[2*ni+1],st[2*ni+2]);
    }
    else{
      st[ni] = arr[l];
    }
  }
}

int* constructSegmentTree(int* arr, int size){
  int* st = new int[power2(ceilLog2(size)+1)-1];
  fillSegmentTree(arr,st,0,size-1,0);
  return st;
}


int MIN_(int* arr,int a,int b){
  if(a == -1){
    return b;
  }
  else if(b==-1){
    return a;
  }
  if(arr[a]>arr[b]){
    return b;
  }
  return a;
}
int getMINIndex(int* arr,int* st,int ql, int qr,int nl, int nr, int ni){
  if(!(nl>qr || nr<ql)){
    if(nl==nr){
      return nl;
    }
    else{
      int mid = (nl+nr)>>1;
      int leftMinIndex = getMINIndex(arr,st,ql,qr,nl,mid,2*ni+1);
      int rightMinIndex = getMINIndex(arr,st,ql,qr,mid+1,nr,2*ni+2);
      return MIN_(arr,leftMinIndex,rightMinIndex);
    }
  }
  return -1;
}

int getBiggestRect(int*arr,int* st, int size_, int l, int r){
  if(l<=r){
    int minInRange = getMINIndex(arr,st,l,r,0,size_-1,0);
    int size = (r-l+1)*arr[minInRange];
    if(l!=r){
      size = MAX(size,getBiggestRect(arr,st,size_,l,minInRange-1));
      size = MAX(size,getBiggestRect(arr,st,size_,minInRange+1,r));
    }
    return size;
  }
  return -1;
}


int main(int argc, char const *argv[]) {
  int arr[] = {6, 2, 5, 4, 5, 1, 6};
  int* st = constructSegmentTree(arr,7);
  cout<<getBiggestRect(arr,st,7,0,6)<<endl;
  return 0;
}
