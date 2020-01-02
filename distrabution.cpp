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
struct Frac{
	T abv,btm;
	static T gcd(T a,T b){
		if(b > a) return gcd(b,a);
		else if(b == 0) return a;
		else return gcd(b,a%b);
	}
	Frac(T abv_, T btm_){
		T com = Frac<T>::gcd(abv_, btm_);
		abv = abv_/com;
		btm = btm_/com;
		if(btm < 0){
			abv *= -1;
			btm *= -1;
		}
	}
	Frac(): abv(0), btm(1){}
	Frac<T> operator *(Frac<T> b){
		return Frac<T>(abv*b.abv,btm,btm*b.btm);
	}
	Frac<T> operator /(Frac<T> b){
		return Frac<T>(abv*b.btm,btm,btm*b.abv);
	}
	Frac<T> operator +(Frac<T> b){
		return Frac<T>(abv*b.btm + b.abv*btm,b.btm*btm);
	}
	Frac<T> operator -(Frac<T> b){
		return Frac<T>(abv*b.btm - b.abv*btm,b.btm*btm);
	}
};

const Frac<ull> FRAC1(1,1);
const Frac<ull> FRAC0(0,1);
const Frac<ull> FRACNEG1(-1,1);

int N;
Frac<ull> DP[1005][1005];
Frac<ull> Ts[1005];

Frac<ull> dp(int k, int n){
	if(k == 1) return Ts[n-1]/(FRAC1 - Ts[n-1]);
	if(n < k) return FRAC0;
	if(DP[k][n] == FRACNEG1) return DP[k][n];
	DP[k][n] = T[n-1] * (dp(k,n-1)/T[n-2] + dp(k-1,n-1));
	return DP[k][n];
}

template<typename T>
void TRACEV(const Frac<T>& a){
	TRACEV(a.abv); TRACED('/'); TRACEV(a.btm);
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);

	cin>>N;
	FOR(i,1005) FOR(j,1005) DP[i][j] = FRACNEG1;
	ull abv, btm;
	FOR(i,N){
		cin>>abv>>btm;
		Ts[i] = Frac<ull>(abv,btm);
	}
	TRACE(Ts);
	return 0;
}