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
#define ld long double
#define pii pair<int,int>
#define PI 3.141592654

template<typename T>
struct MathVec{
	T x,y;
	MathVec(): x(0), y(0){}
	MathVec(T X, T Y): x(X), y(Y){}
	MathVec<T> add(const MathVec<T>& other){
		return MathVec(x+other.x,y+other.y);
	}
	MathVec<T> neg(const MathVec<T>& other){
		return MathVec(x-other.x,y-other.y);
	}
	ld abs(){
		return sqrt(x*x+y*y);
	}
	T dot(const MathVec<T>& other){
		return x*other.x + y*other.y;
	}
	static bool cmp(const MathVec<T>& a, const MathVec<T>& b){
		if(a.x == b.x) return a.y < b.y;
		return a.x < b.x;
	}
	ld angle_between(MathVec<T>& other){
		ld abs_other = other.abs();
		return acos(dot(other)/(abs() * other.abs()));
	}
	pair<ld,ld> line(const MathVec<T>& other){
		ld m = (ld)(y-other.y)/(x-other.x);
		return pair<ld,ld>{m,y-m*x};
	}
};
template<typename T>
void TRACEV(const MathVec<T>& a){
	cerr<<"("<<a.x<<", "<<a.y<<")";
}

template<typename T>
inline bool cmp_upper(const MathVec<T>& a, const MathVec<T>& b,const MathVec<T>& c){
	return (a.x-b.x)*(c.y-a.y) > (a.y-b.y)*(c.x-a.x);
}

	int N;

template<typename T>
list<int> get_convex_hull(T points){
	list<int> convex_hull = {0,1};
	FORS(2,curCheck,N){
		while(true){
			if(convex_hull.size() == 1){
				convex_hull.push_back(curCheck);
				break;
			}
			int a = *prev(convex_hull.end(),2);
			int b = *prev(convex_hull.end(),1);
			if(cmp_upper(points[a],points[b],points[curCheck])){
				convex_hull.pop_back();
			}
			else{
				convex_hull.push_back(curCheck);
				break;
			}
		}
	}
	return convex_hull;
}

#define print_conv_h FORA(i,convex_hull) {TRACEV(points[i]); _}_N
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin>>N;
	vector<MathVec<ll>> points(N);
	FOR(i,N) cin>>points[i].x>>points[i].y;
	sort(points.begin(),points.end(),MathVec<ll>::cmp);
	auto convex_hull = get_convex_hull(points);
	print_conv_h
	FOR(i,N) points[i].y=-points[i].y;
	convex_hull = get_convex_hull(points);
	FOR(i,N) points[i].y=-points[i].y;
	print_conv_h
	return 0;
}