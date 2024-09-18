#include "prime.hpp"
#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

TEST(prime_factorize, 15) {
   using ll = std::int64_t;
   constexpr ll N = 15;
   const auto expected = std::vector<std::pair<ll, ll>>{
       {3, 1},
       {5, 1},
   };
   const auto actual = prime_factorize<ll>(N);
   ASSERT_EQ(expected, actual);
}

TEST(prime_factorize, 5328972) {
   using ll = std::int64_t;
   constexpr ll N = 5328972;
   const auto expected = std::vector<std::pair<ll, ll>>{
       {2, 2},
       {3, 2},
       {11, 1},
       {13457, 1},
   };
   const auto actual = prime_factorize<ll>(N);
   ASSERT_EQ(expected, actual);
}
