#include <bits/stdc++.h>

using namespace std;

#define FOR(i_,a_) for(int i_=0;i_<a_;++i_)
#define FORR(i_,a_) for(int i_=a_-1;i_>=0;--i_)
#define FORI(i_,a_) for(int i_=1;i_<=a_;++i_)
#define FORA(i_,a_) for(auto i_:a_)
#define FOR1(i_,a_) for(int i_=1;i_<a_;++i_)
#define ll long long int
#define ull unsigned long long int
#define INF INT_MAX
typedef pair<int,int> pii;

int N;
int M;
vector<pii> MST;
vector<vector<pii>> connections;

void setMST(){
	set<pii> queue;
	queue.insert({0,0});
	vector<int> dist(N,INF);
	vector<int> parent(N,-1);
	vector<bool> visited(N,false);
	dist[0] = 0;
	int value, index, weight, otherI;
	while(!queue.empty()){
		tie(value,index) = *queue.begin();
		queue.erase(queue.begin());
		FORA(edge,connections[index]){
			tie(otherI,weight) = edge;
			if(!visited[otherI]){
				if(weight < dist[otherI]){
					if(dist[otherI] != INF){
						queue.erase({dist[otherI],otherI});
					}
					queue.insert({weight,otherI});
					parent[otherI] = index;
					dist[otherI] = weight;
				}
			}
		}
		visited[index] = true;
		if(parent[index] != -1){
			MST.push_back({index,parent[index]});
		}
	}
}


int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin>>N>>M;
	connections.resize(N);
	int a,b,c;
	FOR(i,M){
		cin>>a>>b>>c;
		connections[a].push_back({b,c});
		connections[b].push_back({a,c});
	}
	MST.reserve(N-1);
	setMST();
	FORA(edge,MST){
		printf("%i %i\n",edge.first,edge.second);
	}

	return 0;
}