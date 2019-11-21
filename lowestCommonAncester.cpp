#include <vector>
#include <iostream>

using namespace std;


struct BinaryTreeNode{
  BinaryTreeNode* leftChild;
  BinaryTreeNode* rightChild;

  BinaryTreeNode();
};

struct BinaryHeight{
  BinaryTreeNode* node;
  int level;

  BinaryHeight(BinaryTreeNode* n, int lvl);
};

BinaryTreeNode::BinaryTreeNode(){
  leftChild = NULL;
  rightChild = NULL;
}
BinaryHeight::BinaryHeight(BinaryTreeNode* n, int lvl){
  node = n;
  level = lvl;
}

vector<BinaryHeight*>* constructEulerPath(BinaryTreeNode* node, int level){
  vector<BinaryHeight*>* out = new vector<BinaryHeight*>{new BinaryHeight(node,level)};
  if(node->leftChild == NULL){
    return out;
  }
  vector<BinaryHeight*>* leftChildPath = constructEulerPath(node->leftChild,level+1);
  vector<BinaryHeight*>* rightChildPath = constructEulerPath(node->rightChild,level+1);
  out->reserve(3+leftChildPath->size()+rightChildPath->size());
  for(BinaryHeight* loc : leftChildPath[0]){
    out->push_back(loc);
  }
  delete leftChildPath;
  out->push_back(out[0][0]);
  for(BinaryHeight* loc : rightChildPath[0]){
    out->push_back(loc);
  }
  delete rightChildPath;
  out->push_back(out[0][0]);
  return out;
}

BinaryTreeNode* getCommonAncestor(vector<BinaryHeight*>& eulerTour, )


int main(int argc, char const *argv[]) {
  BinaryTreeNode* root = new BinaryTreeNode();
  root->leftChild = new BinaryTreeNode();
  root->rightChild = new BinaryTreeNode();
  root->leftChild ->leftChild = new BinaryTreeNode();
  root->leftChild ->rightChild = new BinaryTreeNode();
  root->leftChild ->rightChild->leftChild = new BinaryTreeNode();
  root->leftChild ->rightChild->rightChild = new BinaryTreeNode();
  root->rightChild ->leftChild = new BinaryTreeNode();
  root->rightChild ->rightChild = new BinaryTreeNode();

  vector<BinaryHeight*>& eulerTour = *constructEulerPath(root,0);

  for(auto loc: eulerTour){
    cout<<loc->level<<' ';
  }

  return 0;
}
