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
#define TRACED(_v) cerr<<_v;
void TRACEV(string a){TRACED(a);}
void TRACEV(char a){TRACED(a);}
template<typename... Args> void TRACEV(tuple<Args...> t);
template<typename l, typename r> void TRACEV(pair<l,r> t);
template<typename T> void TRACEV(T t){TRACED(t);}
template<template<typename...> class T, typename... K> void TRACEV(T<K...> t);
template<typename T, size_t S> void TRACEV(array<T,S> t){TRACEV("[");TRACEV(t[0]);FOR1(i,S){TRACEV(", ");TRACEV(t[i]);}TRACEV("]");}
template<typename T,typename... Args>void TRACEUT_(T t){TRACEV(t);}
template<typename T,typename... Args>void TRACEUT_(T t, Args... args){TRACEV(t); TRACED(", "); TRACEUT_(args...);}
template<typename T,typename... Args>void TRACEUT(T t, Args... args){TRACED('('); TRACEUT_(t,args...); TRACED(")");}
template<typename Tuple, size_t... Is>void TRACET_(Tuple t, index_sequence<Is...>){TRACEUT(get<Is>(t)...);}
template<typename Tuple>void TRACET(Tuple t){TRACET_(t,make_index_sequence<tuple_size<Tuple>::value>{});}
#define TRACEP(p_) TRACED("("); TRACEV(p_.first);TRACED(", ");TRACEV(p_.second);TRACED(")");
template<typename... Args> void TRACEV(tuple<Args...> t){TRACET(t);}
template<typename l, typename r> void TRACEV(pair<l,r> t){TRACEP(t);}
template<template<typename...> class T, typename... K> void TRACEV(T<K...> t){if(t.empty()){TRACEV("[]");return;}auto it = t.begin();
TRACED("[");TRACEV(*it);for(++it;it!=t.end();++it){TRACED(", ");TRACEV(*it);}TRACED("]");}
template<typename T> void TRACE(T t){TRACEV(t);_N;}
template<typename T,typename... Ts> void TRACE(T t,Ts... args){TRACEV(t); _T; TRACE(args...);}

#define ll long long int
#define ull unsigned long long int
#define pii pair<int,int>

template<typename T>
struct BIT{
	vector<T> BIT_;
	inline size_t size(){return BIT_.size();}
	template<typename I>
	void update(I i, T inc){
		i = i + 1;
		while(i < size()){
			BIT_[i] += inc;
			i += i&-i;
		}
	}
	template<typename I>
	T query(I i){
		i = i + 1;
		T out = BIT_[0];
		while(i > 0){
			out += BIT_[i];
			i -= i&-i;
		}
		return out;
	}
	template<typename I>
	T query(I l, I r){
		return query(r)-query(l-1);
	}
	template<typename C, typename... ADD>
	BIT(const C& c){
		BIT_ = vector<T>(c.size()+1,0);
		int i = 0;
		for(T val : c){
			update(i,val);
			++i;
		}
	}
	BIT(){}
	void resize(size_t N){
		BIT_.resize(N,0);
	}
};

template<typename T>
struct BITExt{
	BIT<T> bit1,bit2;
	BITExt(size_t N){
		bit1.resize(N+1);
		bit2.resize(N+1);
	}
	template<typename I>
	void update(I l, I r, T inc){
		bit1.update(l,inc);
		bit1.update(r+1,-inc);
		bit2.update(l,inc*(l-1));
		bit2.update(r+1,-inc*r);
	}
	template<typename I>
	T query(I i){
		return bit1.query(i)*i - bit2.query(i);
	}
	template<typename I>
	T query(I l, I r){
		return query(r) - query(l-1);
	}
};


int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	BITExt<ll> bit(10e5);
	FOR(i,10e5){
		bit.update(0,i,1);
	}
	cout<<bit.query(0,(int)10e5-1)<<'\n';
	return 0;
}