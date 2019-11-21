#include <map>
#include <cstring>
#include <string>

using namespace std;

class TrieNode{
public:
  map<char,TrieNode*> children;
  int index;
  int visited;

  TrieNode(){
    index = -1;
    visited = 0;
  }

  void addWord(char* word, int index_){
    visited++;
    if(word[0] != '\0'){
      if(children.find(word[0]) == children.end()){
        children[word[0]] = new TrieNode();
      }
      children[word[0]]->addWord(word+1,index_);
    }
    else{
      index = index_;
    }
  }

  char* lcp(char* word){
    if(word[0] == '\0'){
      return word;
    }
    if(children.find(word[0]) != children.end()){
      char* childLcp = children[word[0]]->lcp(word+1);
      if(childLcp != NULL){
        return childLcp;
      }
      else{
        return word;
      }
    }
    else{
      return NULL;
    }
  }

  void fillSuffixArray(int* arr, int& index_){
    if(index != -1){
      arr[index_++] = index;
    }
    for(auto child:children){
      child.second->fillSuffixArray(arr,index_);
    }
  }

  pair<char,TrieNode*> mostVisitedChild(){
    pair<char,TrieNode*> out = {'\0',NULL};
    for(auto child: children){
      if(out.first == '\0' || child.second->visited>out.second->visited){
        out = child;
      }
    }
    return out;
  }

  pair<char*,int> longestRepeat(char thisCh,int length){
    pair<char*,int> out = {NULL,0};
    if(visited == 1){
      out = {new char[length],length};
      out.first[length-1] = '\0';
    }
    else if(visited > 1){
      pair<char*,int> childStr;
      for(auto child : children){
        childStr = child.second->longestRepeat(child.first,length+1);
        if(childStr.second > out.second){
          out = childStr;
        }
      }
      if(length >= 0){
        out.first[length-1] = thisCh;
      }
    }
    return out;
  }
};

class SuffixTree{
public:
  TrieNode* root;
  char word[];

  SuffixTree(const char* word_){
    memcpy(word,word_,strlen(word_)+1);
    root = new TrieNode();
    char* current = word;
    while(current[0] != '\0'){
      root->addWord(current,current-word);
      current = current + 1;
    }
  }

  char* lcp(char* word_){
    int len = root->lcp(word_) - word_ + 1;
    char* out = new char[len];
    memcpy(out,word_,len);
    out[len] = '\0';
    return out;
  }

  int* getSuffixArray(){
    int* suffixArray = new int[strlen(word)];
    int index = 0;
    root->fillSuffixArray(suffixArray, index);
    return suffixArray;
  }

  char* longestRepeat(){
    return root->longestRepeat(' ',0).first;
  }
};

int main(){
  char word[] = "abcpqrabpqpq";
  SuffixTree mySuffixTree(word);
  printf("%s\n", mySuffixTree.longestRepeat());
}
