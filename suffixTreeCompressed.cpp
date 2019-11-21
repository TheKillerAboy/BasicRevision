#include <map>
#include <string>
#include <cstring>

using namespace std;

class SuffixTreeNode{
public:
  map<string,SuffixTreeNode*> children;
  int index;

  SuffixTreeNode(){
    index = -1;
  }

  void addWord(char* word, int index_){
      if(word[0] != '\0'){
        string firstLet(1,word[0]);
        if(children.find(firstLet) == children.end()){
          children[firstLet] = new SuffixTreeNode();
        }
        children[firstLet]->addWord(word+1,index_);
      }
      else{
        index = index_;
      }
  }

  bool chain(){
    map<string,SuffixTreeNode*> newMap;
    for(auto child:children){
      if(child.second->chain()){
        pair<string,SuffixTreeNode*> childPair = *(child.second->children.begin());
        newMap[child.first+childPair.first] = childPair.second;

        delete child.second;
      }
      else{
        newMap[child.first] = child.second;
      }
    }
    children = newMap;

    return children.size() == 1;
  }

  bool hasWord(char* word){
    for(auto child: children){
      int i;
      for(i = 0; i < child.first.length(); i++){
        if(i >= strlen(word)){
          return true;
        }
        if(word[i] != child.first[i]){
          break;
        }
      }
      if(i==child.first.length()){
        return hasWord(word+child.first.length());
      }
    }
  }
};


class SuffixTree{
public:
  SuffixTreeNode* root;
  char word[];

  SuffixTree(const char* word_){
    memcpy(word,word_,strlen(word_)+1);
    root = new SuffixTreeNode();
    char* current = word;
    while(current[0] != '\0'){
      root->addWord(current,current-word);
      current = current + 1;
    }
    root->chain();
  }
};
