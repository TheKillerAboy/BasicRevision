#include <bits/stdc++.h>

using namespace std;

#define FOR(i_,a_) for(int i_=0;i_<a_;++i_)
#define FORR(i_,a_) for(int i_=a_-1;i_>=0;--i_)
#define FORI(i_,a_) for(int i_=1;i_<=a_;++i_)
#define FORA(i_,a_) for(auto i_:a_)
#define FOR1(i_,a_) for(int i_=1;i_<a_;++i_)
#define ll long long int
#define ull unsigned long long int

struct Edge{
	int nodeA,nodeB;
	int weight;

	Edge(int a,int b, int w) :nodeA(a),nodeB(b),weight(w){}
	Edge():nodeA(0),nodeB(0),weight(0){}
};

int N;
int M;
vector<Edge> edges;
vector<Edge> MST;
vector<int> parents;

inline int uFind(int a){
	int b = a;
	while(parents[b] != -1){
		b = parents[b];
	}
	if(a != b){
		parents[a] = b;
	}
	return b;
}

inline void uMerge(int a, int b){
	int aParent = uFind(a);
	int bParent = uFind(b);
	if(aParent == a){
		parents[a] = bParent;
	}
	else if(bParent == b){
		parents[b] = aParent;
	}
	else{
		parents[aParent] = bParent;
	}
}

void setMST(){
	auto cmp = [](Edge& a, Edge& b)->bool{return a.weight<b.weight;};
	sort(edges.begin(),edges.end(),cmp);
	FORA(edge,edges){
		if(MST.size() == N-1){
			break;
		}
		if(uFind(edge.nodeA) != uFind(edge.nodeB)){
			MST.push_back(edge);
			uMerge(edge.nodeA,edge.nodeB);
		}
	}
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin>>N>>M;
	edges.resize(M);
	int a,b,c;
	FOR(i,M){
		cin>>a>>b>>c;
		edges[i] = Edge(a,b,c);
	}
	parents.resize(N,-1);
	MST.reserve(N-1);
	setMST();
	FORA(edge,MST){
		printf("%i %i %i\n",edge.nodeA,edge.nodeB,edge.weight);
	}
	return 0;
}

/*
8
11
0 3 4
0 7 3
0 1 5
1 2 10
2 5 7
5 6 5
1 4 8
1 3 2
3 6 6
4 6 9
6 7 8
*/