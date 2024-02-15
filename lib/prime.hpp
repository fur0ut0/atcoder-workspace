#include <vector>
using namespace std;

//------------------------------------------------------------------------------

template <typename T>
vector<T> prime_factorize(T n) {
   vector<T> v;
   for (T i = 2; i * i <= n; ++i) {
      while (n % i == 0) {
         v.push_back(i);
         n /= i;
      }
   }
   if (n > 1) {
      v.push_back(n);
   }
   return v;
}

template <typename T>
bool is_prime(T n) {
   for (T i = 2; i * i <= n; ++i) {
      if (n % i == 0) {
         return false;
      }
   }
   return true;
}