#include <vector>
#include <cmath>
#include <list>
#include <tuple>
#include <map>
#include <set>

using namespace std;

class SegmentTree{
public:
  static int MAX(int a, int b){
    if(a>b){
      return a;
    }
    return b;
  }
  static int MIN(int a, int b){
    if(a>b){
      return b;
    }
    return a;
  }

  vector<int> arr;
  int n;

  vector<int> st;

  int (*cmp)(int,int);

  SegmentTree(){;}
  SegmentTree(vector<int> arr_, int n_,int (*cmp_)(int,int) = SegmentTree::MAX){
    arr = arr_;
    n = n_;
    cmp = cmp_;
    st.resize((int)pow(2,ceil(log2(n))+1)-1);
    fillSegmentTree(0,n-1,0);
  };

  int cmp_wrapper(int a, int b){
    if(a == -1){
      return b;
    }
    else if(b == -1){
      return a;
    }
    return cmp(a,b);
  }

  void fillSegmentTree(int nl, int nr, int ni){
    if(nl<nr){
      int mid = (nl+nr)>>1;

      fillSegmentTree(nl,mid,2*ni+1);
      fillSegmentTree(mid+1,nr,2*ni+2);

      st[ni] = cmp_wrapper(st[2*ni+1],st[2*ni+2]);
    }
    else if(nl==nr){
      st[ni] = arr[ni];
    }
  }

  int _inRange(int ql, int qr, int nl, int nr, int ni){
    if(ql<=nl && nr<=qr){
      return st[ni];
    }
    else if(nr<ql || nl>qr){
      return -1;
    }
    else{
      int mid = (nl+nr)>>1;

      return cmp_wrapper(_inRange(ql,qr,nl,mid,2*ni+1),_inRange(ql,qr,mid+1,nr,2*ni+2));
    }
  }

  int inRange(int ql, int qr){
    return _inRange(ql,qr,0,n-1,0);
  }

  int bestIndex(int a, int b){
      if(a == -1){
        return b;
      }
      else if(b == -1){
        return a;
      }
      if(cmp(arr[a],arr[b])){
        return a;
      }
      return b;
  }

  int _inRangeIndex(int ql, int qr, int nl, int nr, int ni){
    if(!(nr<ql || nl>qr)){
      if(nl == nr){
        return nl;
      }
      else{
        int mid = (nl+nr)>>1;
        return bestIndex(_inRangeIndex(ql,qr,nl,mid,2*ni+1),_inRangeIndex(ql,qr,mid+1,nr,2*ni+2));
      }
    }
    return -1;
  }

  int inRangeIndex(int ql, int qr){
    return _inRangeIndex(ql,qr,0,n-1,0);
  }
};

class TreeNode;

class Chain{
public:
  static map<TreeNode*,Chain*> chains;

  vector<TreeNode*> contained;

  SegmentTree st;

  Chain(){;}

  static void fillChains(TreeNode* root);
  static void _addChains(Chain* thisChain,TreeNode* root);

  void initST();
};

class TreeNode{
public:
  static vector<int> eulerHeights;
  static vector<TreeNode*> eulerNodes;
  static SegmentTree eulerST;
  static map<TreeNode*,set<int>> eulerIndexs;

  vector<TreeNode*> children;
  int parentWeight;
  int rootedHeight;

  TreeNode(){;}

  void claculateRootedHeight(){
    rootedHeight = 1;
    for(auto child: children){
      child->claculateRootedHeight();
      rootedHeight+=child->rootedHeight;
    }
  }

  void _eulerPath(list<int>& heights, list<TreeNode*>& nodes, int height){
    heights.push_back(height);
    nodes.push_back(this);
    eulerIndexs[this].insert(heights.size() - 1);
    for(auto child:children){
      child->_eulerPath(heights,nodes,height+1);

      heights.push_back(height);
      nodes.push_back(this);
      eulerIndexs[this].insert(heights.size() - 1);
    }
  }

  // Root functions
  void eulerPath(){
    list<int> heights;
    list<TreeNode*> nodes;

    _eulerPath(heights,nodes,0);

    copy(heights.begin(),heights.end(),back_inserter(eulerHeights));
    copy(nodes.begin(),nodes.end(),back_inserter(eulerNodes));

    eulerST = SegmentTree(eulerHeights,eulerHeights.size(),SegmentTree::MIN);
  }

  void constructChains(){
    Chain::fillChains(this);
  }

  void finalizeTree(){
    eulerPath();
    constructChains();
  }

  static TreeNode* LCA(TreeNode* a,TreeNode* b){
    int leftIndex = *eulerIndexs[a].begin();
    int rightIndex = *eulerIndexs[b].lower_bound(leftIndex+1);
    return eulerNodes[eulerST.inRangeIndex(leftIndex,rightIndex)];
  }

  static vector<TreeNode*> getPath(TreeNode* a,TreeNode* b){
    int leftIndex = *eulerIndexs[a].begin();
    int rightIndex = *eulerIndexs[b].lower_bound(leftIndex+1);
    vector<TreeNode*> out;
    out.reserve(rightIndex-leftIndex+1);
    for(int i = leftIndex; i <= rightIndex; i++){
      out[leftIndex-i] = eulerNodes[i];
    }
    return out;
  }
};

void Chain::_addChains(Chain* thisChain,TreeNode* root){
  pair<int,TreeNode*> best = {0,NULL};
  chains[root] = thisChain;
  thisChain->contained.push_back(root);

  for(auto child:root->children){
    if(child->rootedHeight > best.first){
      best = {child->rootedHeight,child};
    }
  }
  for(auto child:root->children){
    if(child == best.second){
      _addChains(thisChain,child);
    }
    else{
      Chain* newChain = new Chain();
      _addChains(newChain,child);
    }
  }
}

void Chain::initST(){
  vector<int> values;
  values.reserve(contained.size());
  for(auto node: contained){
    values.push_back(node->parentWeight);
  }
  st = SegmentTree(values,values.size());
}

void Chain::fillChains(TreeNode* root){
  _addChains(new Chain(),root);
  for(auto chain: chains){
    chain.second->initST();
  }
}
