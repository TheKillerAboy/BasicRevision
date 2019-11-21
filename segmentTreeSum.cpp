#include <vector>
#include <iostream>

using namespace std;

class SegmentNode{
public:
  int left, right, value;
  SegmentNode* leftChild;
  SegmentNode* rightChild;

  SegmentNode(int val,int l,int r);

  static SegmentNode* createSegment(vector<int>& values, int l, int r);

  int getSum(int l, int r);
  void changeValue(int i, int value_);
};

SegmentNode::SegmentNode(int val,int l,int r){
  value = val;
  left = l;
  right = r;
  leftChild = NULL;
  rightChild = NULL;
}

SegmentNode* SegmentNode::createSegment(vector<int>& values, int l, int r){
  if(l>r){
    return NULL;
  }
  SegmentNode* output = new SegmentNode(0,l,r);
  if(l == r){
    output->value = values[l];
  }
  else{
    int m = (l+r)>>1;
    output->leftChild = createSegment(values,l,m);
    output->rightChild = createSegment(values,m+1,r);
    output->value = output->leftChild->value+output->rightChild->value;
  }
  return output;
}

int SegmentNode::getSum(int l, int r){
  if(left>=l&&right<=r){
    return value;
  }
  else if(right<l||left>r){
    return 0;
  }
  else{
    return leftChild->getSum(l,r)+rightChild->getSum(l,r);
  }
}
void SegmentNode::changeValue(int i, int value_){
  if(left<=i && i<=right){
    if(left==right){
      value = value_;
      return;
    }
    leftChild->changeValue(i,value_);
    rightChild->changeValue(i,value_);
    value = leftChild->value + leftChild->value;
  }
}

class SegmentTree{
public:
  SegmentNode* root;

  SegmentTree(vector<int>& values);
  int getSum(int l, int r);
  void changeValue(int i, int value);
};

SegmentTree::SegmentTree(vector<int>& values){
  root = SegmentNode::createSegment(values,0,values.size()-1);
}
int SegmentTree::getSum(int l, int r){
  return root->getSum(l,r);
}
void SegmentTree::changeValue(int i, int value){
  root->changeValue(i,value);
}

int main(int argc, char const *argv[]) {
  vector<int> values = {1,2,3,4,5};
  SegmentTree myTree(values);
  cout<<myTree.getSum(1,3)<<endl;
  return 0;
}
