#include <iostream>
#include <set>
#include <vector>
#include <cmath>

using namespace std;

#define ll long long int

set<ll> primes = {2,3,5};
ll last_check = 5;

void primes_to(ll a){
  if(last_check >= a){
    return;
  }
  bool isPrime;
  for(ll i = last_check + 2; i <= a; i+=2){
    isPrime = true;
    for(ll prime : primes){
      if(i % prime == 0){
        isPrime = false;
        break;
      }
      if(prime >= sqrt(i)){
        break;
      }
    }
    if(isPrime){
      primes.insert(i);
    }
  }
  last_check = a-1+a%2;
}

bool isPrime(ll a){
  primes_to(a);
  return primes.find(a) != primes.end();
}

vector<ll> divisors(ll a){
  primes_to(a);
  vector<ll> out;
  auto currentPrimeIT = primes.begin();
  while(a > 1){
    if(a%(*currentPrimeIT) == 0){
      out.push_back(*currentPrimeIT);
      a/=*currentPrimeIT;
    }
    else{
      advance(currentPrimeIT,1);
    }
  }
  return out;
}

vector<ll> factors(ll a){
  primes_to(a);
    vector<ll> out;
    for(ll prime : primes){
      if(a%prime == 0){
        while(a%prime == 0){
          a/=prime;
        }
        out.push_back(prime);
      }
      if(a == 1){
        break;
      }
    }
    return out;
}

vector<ll> factors_(ll n){
    vector<ll> out;
    if(n%2 == 0){
      out.push_back(2);
      while (n % 2 == 0)
      {
          n = n/2;
      }
    }
    for (ll i = 3; i <= sqrt(n); i = i + 2)
    {
        if(n%i == 0){
          while (n % i == 0)
          {
              n = n/i;
          }
              out.push_back(i);
        }
    }
    if (n > 2){
        out.push_back(n);
      }
    return out;
}

int main(){
  for(ll factor : factors((ll)999999)){
    cout<<factor<<" ";
  }
}
