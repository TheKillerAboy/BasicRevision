#include <vector>
#include <iostream>
#include <climits>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

#define INF (int)LONG_MAX

pair<int,int> __MAX__(pair<int,int> a, pair<int,int> b){
	return max(a,b);
}
pair<int,int> __MIN__(pair<int,int> a, pair<int,int> b){
	return min(a,b);
}

struct Node{
	int chainID;
	int sTIndex;
	int eulerPathIndex;
	int rootedChildren;
	int value;
	int parent;
	vector<int> children;
};

struct Chain{
	int root;

	Chain(int root_){
		root = root_;
	}
};

struct EulerPathNode{
	int depth;
	int nodeID;

	EulerPathNode(int nodeID_, int depth_){
		nodeID = nodeID_;
		depth = depth_;
	}
};

vector<Node*> nodes;
vector<Chain*> chains;
vector<pair<int,int>> chainST; // value , ID
vector<pair<int,int>> chainArr; //value, ID

vector<EulerPathNode*> eulerPath;
vector<pair<int,int>> eulerPathArr; //value, ID
vector<pair<int,int>> eulerPathST; //value, ID

void fillRootedChildren(int curNode){
	nodes[curNode]->rootedChildren = 1;
	for(int child : nodes[curNode]->children){
		fillRootedChildren(child);
		nodes[curNode]->rootedChildren+=nodes[child]->rootedChildren;
		nodes[child]->parent = curNode;
	}
}

void constructChain(int curNode, int curChain, bool isRoot = false){
	if(isRoot){
		chains.push_back(new Chain(curNode));
		curChain = chains.size() - 1;
	}
	chainArr.push_back({nodes[curNode]->value,curNode});
	nodes[curNode]->chainID = curChain;
	nodes[curNode]->sTIndex = chainArr.size()-1;
	pair<int,int> bestChild = {-1,-1};
	for(int child : nodes[curNode]->children){
		bestChild = max(bestChild,pair<int,int>{nodes[child]->rootedChildren,child});
	}
	for(int child : nodes[curNode]->children){
		if(child == bestChild.second){
			constructChain(child,curChain);
		}
		else{
			constructChain(child,-1,true);
		}
	}
}

void constructEulerPath(int curNode, int depth){
	eulerPath.push_back(new EulerPathNode(curNode,depth));
	eulerPathArr.push_back({depth,curNode});
	nodes[curNode]->eulerPathIndex = eulerPath.size()-1;
	for(int child : nodes[curNode]->children){
		constructEulerPath(child,depth+1);
		eulerPath.push_back(new EulerPathNode(curNode,depth));
		eulerPathArr.push_back({depth,curNode});
	}
}

void sizeSegmentTree(vector<pair<int,int>>& st, vector<pair<int,int>>& arr){
	st.resize((int)pow(2,ceil(log2(arr.size()))+1)-1);
}

template <typename CMP>
void constructSegmentTree(vector<pair<int,int>>& st, vector<pair<int,int>>& arr, int nl, int nr, int ni, CMP cmp){
	if(nl < nr){
		int mid = (nl+nr)>>1;

		constructSegmentTree(st,arr,nl,mid,2*ni+1,cmp);
		constructSegmentTree(st,arr,mid+1,nr,2*ni+2,cmp);

		st[ni] = cmp(st[2*ni+1],st[2*ni+2]);
	}
	else if(nl == nr){
		st[ni] = arr[nl];
	}
}

template <typename CMP>
pair<int,int> getCMPSegmentTree(vector<pair<int,int>>& st,int ql, int qr, int nl, int nr, int ni, CMP cmp, int defaultV){
	if(ql<=nl && nr <= qr){
		return st[ni];
	}
	else if(nl > qr || nr < ql){
		return {defaultV,-1};
	}
	else{
		int mid = (nl+nr)>>1;
		return cmp(getCMPSegmentTree(st,ql,qr,nl,mid,2*ni+1,cmp,defaultV),getCMPSegmentTree(st,ql,qr,mid+1,nr,2*ni+2,cmp,defaultV));
	}
}

int LCA(int nodeL, int nodeR){
	if(nodeL>nodeR){
		nodeL = nodeL^nodeR;
		nodeR = nodeL^nodeR;
		nodeL = nodeL^nodeR;
	}
	int ePL = nodes[nodeL]->eulerPathIndex;
	int ePR = nodes[nodeR]->eulerPathIndex;
	return eulerPath[getCMPSegmentTree(eulerPathST,ePL,ePR,0,eulerPathArr.size()-1,0,__MIN__,INF).second]->nodeID;
}

int MaxValueBetweenRoot(int node, int nodeRoot){
	int out = -1;
	int curChain = nodes[node]->chainID;
	int curNode = node;
	while(curChain != nodes[nodeRoot]->chainID){
		int nextNode = chains[curChain]->root;
		out = max(out,getCMPSegmentTree(chainST,nodes[curNode]->sTIndex,nodes[nextNode]->sTIndex,0,chainArr.size()-1,0,__MAX__,-1).first);
		curNode = nodes[nextNode]->parent;
	}
	out = max(out,getCMPSegmentTree(chainST,nodes[curNode]->sTIndex,nodes[nodeRoot]->sTIndex,0,chainArr.size()-1,0,__MAX__,-1).first);
	return out;
}

int MaxValueBetween(int nodeL, int nodeR){
	int nodeLCA = LCA(nodeL,nodeR);
	if(nodes[nodeL]->chainID != nodes[nodeR]->chainID){
		return max(MaxValueBetween(nodeL,nodeLCA),MaxValueBetween(nodeR,nodeLCA));
	}
		return getCMPSegmentTree(chainST,nodes[nodeL]->sTIndex,nodes[nodeR]->sTIndex,0,chainArr.size()-1,0,__MAX__,-1).first;
}

void setup(){
	fillRootedChildren(0);
	constructChain(0,0,true);
	constructEulerPath(0,0);

	sizeSegmentTree(eulerPathST,eulerPathArr);
	sizeSegmentTree(chainST,chainArr);

	constructSegmentTree(eulerPathST,eulerPathArr,0,eulerPathArr.size()-1,0,__MIN__);
	constructSegmentTree(chainST,chainArr,0,chainArr.size()-1,0,__MAX__);
}