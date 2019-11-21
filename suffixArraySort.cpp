#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

struct Suffix{
  int index;
  int rank[2];
};

int suffixValue(Suffix a){
  return 26*a.rank[0]+a.rank[1];
}

int getMax(Suffix* arr, int n){
  int a = 0;
  for(int i = 0; i < n; i++){
    if(suffixValue(arr[i]) > a){
      a = suffixValue(arr[i]);
    }
  }
  return a;
}

void countSort(Suffix* arr, int n, int exp){
  Suffix output[n];
  int i, count[10] = {0};

  for(i = 0; i < n; i++){
    count[(suffixValue(arr[i])/exp)%10]++;
  }
  for(i = 1; i < 10; i++){
    count[i] += count[i-1];
  }
  for(i = n-1; i>=0; i--){
    output[count[(suffixValue(arr[i])/exp)%10]-1] = arr[i];
    count[(suffixValue(arr[i])/exp)%10]--;
  }
  for(i = 0; i < n; i++){
    arr[i] = output[i];
  }
}

void radixSort(Suffix* arr, int n){
  int m = getMax(arr,n);

  for(int exp = 1; m/exp > 0; exp*=10){
    countSort(arr,n,exp);
  }
}

bool cmp(Suffix a,Suffix b){
  if(a.rank[0] == b.rank[0]){
    if(a.rank[1]<b.rank[1]){
      return true;
    }
  }
  else if(a.rank[0]<b.rank[0]){
    return true;
  }
  return false;
}

int* buildSuffixArray(char* txt, int n){
  Suffix suffixes[n];

  for(int i = 0; i < n; i++){
    suffixes[i].index = i;
    suffixes[i].rank[0] = txt[i]-'a'+1;
    if(i+1<n){
      suffixes[i].rank[1] = txt[i+1]-'a'+1;
    }
    else{
      suffixes[i].rank[1] = 0;
    }
  }

  radixSort(suffixes,n);
  // sort(suffixes,suffixes+n,cmp);

  int ind[n];

  for(int k = 4; k < 2*n; k*=2){
    int rank = 0;
    int prev_rank = suffixes[0].rank[0];
    suffixes[0].rank[0] = rank;
    ind[suffixes[0].index] = 0;

    for(int i = 1; i < n; i++){
      if(suffixes[i].rank[0] == prev_rank&&suffixes[i].rank[1] == suffixes[i-1].rank[1]){
          prev_rank = suffixes[i].rank[0];
          suffixes[i].rank[0] = rank;
      }
      else{
          prev_rank = suffixes[i].rank[0];
          suffixes[i].rank[0] = ++rank;
      }

      ind[suffixes[i].index] = i;
    }

    for(int i = 0; i < n; i++){
      int nextindex = suffixes[i].index + k/2;
      if(nextindex < n){
        suffixes[i].rank[1] = suffixes[ind[nextindex]].rank[0];
      }
      else{
        suffixes[i].rank[1] = 0;
      }
    }


    // sort(suffixes,suffixes+n,cmp);
    radixSort(suffixes,n);
  }

  int* suffixArr = new int[n];
  for(int i =0; i < n; i++){
    suffixArr[i] = suffixes[i].index;
  }
  return suffixArr;
}

int main(){
  char word[] = "banana";
  int n = strlen(word);
  int* suffixArr = buildSuffixArray(word,n);
  for(int i = 0; i < n; i++){
    printf("%i\n", suffixArr[i]);
  }
}
