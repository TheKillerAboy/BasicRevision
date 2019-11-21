#include <iostream>

using namespace std;

#define ll long long int

const int MOD = (int)10e+9+7;

constexpr int factorial(ll N){
  return N <= 1 ? 1 : (N * factorial(N - 1));
}

int main(){
  constexpr int f = factorial(10);
  cout<<f<<endl;
}
