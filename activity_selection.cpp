#include <bits/stdc++.h>

using namespace std;

#define FOR(i_,a_) for(int i_=0;i_<a_;++i_)
#define FORS(s_,i_,a_) for(int i_=s_;i_<a_;++i_)
#define FORR(i_,a_) for(int i_=a_-1;i_>=0;--i_)
#define FORI(i_,a_) for(int i_=1;i_<=a_;++i_)
#define FORA(i_,a_) for(auto i_:a_)
#define FOR1(i_,a_) for(int i_=1;i_<a_;++i_)
#define FORIT(it_,c_) for(auto it_ = c_.begin(); it_!=c_.end();++it_)

#define _ cerr<<' ';
#define _N cerr<<'\n';
#define _T cerr<<'\t';
#define TRACEV(v_) cerr<<v_;
#define TRACEP(p_) cerr<<"("<<p_.first<<", "<<p_.second<<") ";
#define TRACECE(c_,tt_) for(auto e_:c_){tt_(e_);_;}_N;
#define TRACEC(c_) TRACECE(c_,TRACEV)
#define TRACEE(v_,tt_) tt_(v_);_N;
#define TRACE(v_) TRACEE(v_,TRACEV);
#define TRACEEP(v_) TRACEE(v_,TRACEP);

#define ll long long int
#define ull unsigned long long int
#define pii pair<int,int>

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int N;
	cin>>N;
	vector<pii> activites(N);
	set<pii> start;
	set<pii> end;
	int a,b;
	FOR(i,N){
		cin>>a>>b;
		activites[i] = {a,b};
		start.insert({a,i});
		end.insert({b,i});
	}
	int fE,fEI;
	int fS,fSI;
	int count = 0;
	while(!end.empty()){
		++count;
		tie(fE,fEI) = *end.begin();
		end.erase(end.begin());
		start.erase(start.find({activites[fEI].first,fEI}));
		while(!start.empty() && (*start.begin()).first < fE){
			tie(fS,fSI) = *start.begin();
			start.erase(start.begin());
			end.erase(end.find({activites[fSI].second,fSI}));
		}
	}
	cout<<count<<'\n';


	return 0;
}