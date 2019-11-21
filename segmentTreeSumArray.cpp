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

int GCD(int a, int b){
  if(a == -1){
    return b;
  }
  else if(b==-1){
    return a;
  }
  if(a>=b){
    if(b == 0){
      return a;
    }
    return GCD(b,a%b);
  }
  else{
    return GCD(b,a);
  }
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

void fillSegmentTree(int* arr,int* st, int l, int r, int ni){
  if(l<=r){
    if(l!=r){
      int mid = (l+r)>>1;
      fillSegmentTree(arr,st,l,mid,2*ni + 1);
      fillSegmentTree(arr,st,mid+1,r,2*ni + 2);
      st[ni] = GCD(st[2*ni+1],st[2*ni+2]);
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

int getGCD(int* st,int ql, int qr,int nl, int nr, int ni){
  if(ql<=nl && qr>=nr){
    return st[ni];
  }
  else if(nl>qr || nr<ql){
    return -1;
  }
  else{
    int mid = (nl+nr)>>1;
    return GCD(getGCD(st,ql,qr,nl,mid,2*ni+1),getGCD(st,ql,qr,mid+1,nr,2*ni+2));
  }
}

void updateRange(int* st, int ql, int qr, int nl, int nr, int ni, int update){
    if(!(nl>qr || nr<ql)){
      if(nl==nr){
        st[ni]+=update;
        return;
      }
      int mid = (nl+nr)>>1;
      updateRange(st,ql,qr,nl,mid,2*ni+1,update);
      updateRange(st,ql,qr,mid+1,nr,2*ni+2,update);

      st[ni] = GCD(st[2*ni+1],st[2*ni+2]);
    }
}

int binarySearchSegment(int* st, int ql, int qr, int nl, int nr, int ni, int k){
  if(nl<nr){
    int size;
    if(getGCD(st,ql,qr,nl,nr,ni) == k){
      size = nr-nl+1;
    }
    else{
      size = -1;
    }
    int mid = (nl+nr)>>1;
    size = MIN(size,binarySearchSegment(st,ql,qr,nl,mid,2*ni+1,k));
    size = MIN(size,binarySearchSegment(st,ql,qr,mid+1,nr,2*ni+2,k));
    return size;
  }
  else if(nl==nr){
      if(st[ni] == k){
        return 1;
      }
  }
  return -1;
}

int getSmallest(int* st, int size_, int k){
  int size = -1;
  for(int i = 0; i < size_; i++){
    size = MIN(size,binarySearchSegment(st,i,size_-1,0,size_-1,0,k));
  }
  return size;
}

int main(int argc, char const *argv[]) {
  int arr[] = {6, 9, 7, 10, 12,
                24, 36, 27};
  int* st = constructSegmentTree(arr,8);
  cout<<getSmallest(st,8,3)<<endl;
  return 0;
}
