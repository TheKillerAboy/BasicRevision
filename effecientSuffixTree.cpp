#define END -1

#include <map>
#include <iostream>

using namespace std;

class Edge;

class Node{
public:
  Node* linkedNode;
  map<int,Edge*> edges;

  Node(){
    linkedNode = NULL;
  }
  bool hasEdge(int e){
    return edges.find(e) != edges.end();
  }
};

class Edge{
public:
  int left_bound, right_bound;
  Node* endNode;

  Edge(int lb, int rb){
    left_bound = lb;
    right_bound = rb;
  }

  int size(int end){
    return (right_bound == END ? end : right_bound) - left_bound + 1;
  }

  int indexActiveLength(int activeLength){
    return left_bound + activeLength;
  }

  void setBoundActiveLength(int activeLength){
    right_bound = left_bound + activeLength;
  }
};

int* processWord(string word){
  map<char,int> mapped;
  for(int i = 0; i < word.length(); i++){
    if(mapped.find(word[i]) == mapped.end()){
      mapped[word[i]] = i;
    }
  }
  int* output = new int[word.length()];
  for(int i = 0; i < word.length(); i++){
    output[i] = mapped[word[i]];
  }
  return output;
}

int main(){
  string word = "mississi$";
  int* wordInd = processWord(word);
  int remaining = 0, end = -1, activeEdge = -1, activeLength = 0;
  Node* activeNode = new Node();
  for(int i = 0; i < word.length(); i++){
    remaining++;
    end++;
    while(remaining > 0){
      if(activeLength == 0){
        if(activeNode->hasEdge(wordInd[i])){
          activeLength++;
          activeEdge = wordInd[i];
          break;
        }
        else{
          activeNode->edges[wordInd[i]] = new Edge(i,END);
          remaining--;
        }
      }
      else{
        if(activeNode->edges[activeEdge]->size(end) < activeLength){
          activeNode = activeNode->edges[activeEdge]->endNode;
          activeLength = 0;
        }
        else{
          if(wordInd[activeNode->edges[activeEdge]->indexActiveLength(activeLength)] == wordInd[i]){
            activeLength++;
          }
          else{
            int right_bound = activeNode->edges[activeEdge]->right_bound;
            activeNode->edges[activeEdge]->setBoundActiveLength(activeLength);
            int left_bound = activeNode->edges[activeEdge]->right_bound + 1;

            activeNode->edges[activeEdge]->endNode = new Node();
            Node* childNode = activeNode->edges[activeEdge]->endNode;
            childNode->linkedNode = activeNode;
            childNode->edges[wordInd[left_bound]] = new Edge(left_bound,right_bound);
            childNode->edges[wordInd[i]] = new Edge(i,END);
            activeNode = activeNode->linkedNode;
          }
        }
      }
    }
  }
}
