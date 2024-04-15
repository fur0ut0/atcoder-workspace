#include <vector>
using namespace std;

//------------------------------------------------------------------------------

/**
 * @return pairs of prime and its exponent value
 */
template <typename I, typename T>
vector<pair<T, I>> prime_factorize(T n) {
   vector<pair<T, I>> v;
   for (T i = 2; i * i <= n; ++i) {
      I e = 0;
      while (n % i == 0) {
         ++e;
         n /= i;
      }
      if (e > 0) {
         v.push_back({i, e});
      }
   }
   if (n > 1) {
      v.push_back({n, 1});
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

template <typename T>
vector<T> factorize(T n) {
   vector<T> v;
   for (T i = 2; i * i <= n; ++i) {
      if (n % i == 0) {
         v.push_back(i);
         if (i * i < n) {
            v.push_back(n / i);
         }
      }
   }
   return v;
}

template <typename T>
T sieve(T n) {
   constexpr size_t MAX_N = 1'000'000;
   bool is_prime[MAX_N + 1];
   fill(is_prime, is_prime + MAX_N + 1, true);
   is_prime[0] = false;
   is_prime[1] = false;
   T size = 0;
   for (T i = 2; i <= n; ++i) {
      if (is_prime[i]) {
         ++size;
         for (T j = 2 * i; j <= n; j += i) {
            is_prime[j] = false;
         }
      }
   }
   return size;
}
