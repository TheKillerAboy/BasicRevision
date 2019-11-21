#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int* processPattern(char* pattern, int pN){
  int* pat = new int[pN];
  int last = 0;
  pat[0] = 0;
  for(int i = 1; i < pN; i++){
    if(pattern[last] == pattern[i]){
      pat[i] = ++last;
    }
    else{
      last = 0;
      pat[i] = 0;
    }
  }
  return pat;
}

vector<int> getPosOfPattern(char* word, int wN, char* pattern, int pN){
  int* patternPros = processPattern(pattern,pN);
  int patIndex = 0;
  vector<int> out;
  int i = 0;
  while(i < wN){
    if(word[i] == pattern[patIndex]){
      i++;
      patIndex++;
    }
    if(patIndex == pN){
      patIndex = patternPros[patIndex - 1];
      out.push_back(i - pN + 1);
    }
    else if(i < wN && pattern[patIndex] != word[i]){
      if(patIndex != 0){
        patIndex = patternPros[patIndex - 1];
      }
      else{
        i++;
      }
    }
  }

  return out;
}

int main(){
  char word[] = "AAACAAAAhgfedhdeAAAAC";
  char pat[] = "AAACAAAAAC";
  for(auto pos : getPosOfPattern(word,strlen(word),pat,strlen(pat))){
    printf("%i\n", pos);
  }
  return 0;
}
