#include <map>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

class SuffixNode{
public:
  map<char,SuffixNode*> children;
  string rest;
  int index;

  void addWord(char* word, int _index){
    char* current = word;
    while(current[0] != '\0'){
      if(current-word < rest.size()){
        if(rest[current-word] == current[0]){
          current = current + 1;
        }
        else{
          SuffixNode* newNode = new SuffixNode(rest.substr(current-word+1), index);
          newNode->children = children;
          children.clear();
          children[rest[current-word]] = newNode;
          index = -1;
          rest = rest.substr(0,current-word);
          break;
        }
      }
      else{
        if(children.size() == 0){
          rest = rest + string(current);
        }
        else{
          children[current[0]] = new SuffixNode(string(current+1), _index);
        }
        break;
      }
    }
  }

  SuffixNode(string rest_ = "", int index_ = -1){
    rest = rest_;
    index = index_;
  }

  bool hasWord(char* word){
    char* current = word;
    while(current[0] != '\0'){

    }
    if(current[0] == '\0'){
      return index != -1;
    }
  }
};

int main(){
  SuffixNode* rootTo_myTrie = new SuffixNode();
  char word[] = "hello";
  for(int i = 0; i < strlen(word); i++){
    rootTo_myTrie->addWord(word + i,i);
  }

  return 0;
}
