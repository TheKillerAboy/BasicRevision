#include <iostream>
#include <memory>
#include <utility>
#include <cmath>
#include <climits>

using namespace std;

typedef pair<int,int> Coor;

#define X first
#define Y second

#define INF LONG_MAX

int getAL(Coor a, bool al){
	if(al){
		return a.Y;
	}
	return a.X;
}

int distance(Coor a, Coor b){
	return pow(a.X-b.X,2)+pow(a.Y-b.Y,2);
}

class d2treeNode{
	Coor value;
	unique_ptr<d2treeNode> leftChild;
	unique_ptr<d2treeNode> rightChild;

	d2treeNode(Coor v){
		value = v;
	}

	void push(Coor a, bool al){
		unique_ptr<d2treeNode>* ptrTo;
		if(getAL(a,al) < getAL(value,al)){
			ptrTo = &leftChild;
		}
		else{
			ptrTo = &rightChild;
		}
		unique_ptr<d2treeNode>& refTo = *ptrTo;
		if(refTo){
			refTo->push(a,al);
		}
		else{
			refTo = unique_ptr<d2treeNode>(new d2treeNode(a));
		}
	}

	Coor getMinAL(bool al){
		pair<int,Coor> out = {getAL(value,al),value};
		if(leftChild){
			Coor leftSide = leftChild->getMinAL(al);
			out = min(out,{getAL(leftSide,al),leftSide});
		}
		if(rightChild){
			Coor rightSide = rightChild->getMinAL(al);
			out = min(out,{getAL(rightSide,al),rightSide});
		}
		return out.second;
	}

	bool remove(Coor a, bool al){
		if(value == a){
			if(rightChild){
				Coor minmum = rightChild->getMinAL(al);
				value = minmum;
				if(rightChild->remove(minmum,al+1)){
					rightChild.reset();
				}
			}
			else if(leftChild){
				Coor minmum = leftChild->getMinAL(al);
				value = minmum;
				rightChild = unique_ptr<d2treeNode>(leftChild.release());
				if(rightChild->remove(minmum,al+1)){
					rightChild.reset();
				}
			}
			else{
				return true;
			}
		}
		else{
			unique_ptr<d2treeNode>* ptrTo;
			if(getAL(a,al) < getAL(value,al)){
				ptrTo = &leftChild;
			}
			else{
				ptrTo = &rightChild;
			}
			unique_ptr<d2treeNode>& refTo = *ptrTo;
			if(refTo){
				if(refTo->remove(a,al+1)){
					refTo.reset();
				}
			}
		}
		return false;	
	}

	Coor getClosest(Coor a, bool al){
		pair<int,unique_ptr<d2treeNode>*> ptrTo = {INF,NULL};
		if(leftChild){
			ptrTo = min(ptrTo,{distance(leftChild->value,a),&leftChild});
		}
		if(rightChild){
			ptrTo = min(ptrTo,{distance(leftChild->value,a),&rightChild});
		}
		if(ptrTo.second != NULL){
			unique_ptr<d2treeNode>& refTo = *(ptrTo.second);
			if(distance(a,value) > distance(a,refTo->value)){
				return refTo->value;
			}
		}
		return value;
	}
};