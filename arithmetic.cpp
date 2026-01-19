#include "arithmetic/arithmetic.hpp"
#include "bit_manip/bit_manip.hpp"
#include <cstdint>

uint64_t poly_mul_naive(uint32_t P, uint32_t Q) {
  uint64_t mul = 0;
  int deg_P = degree(P);
  int deg_Q = degree(Q);
  for (int i = 0; i <= deg_P; i++) {
    int p_i = (P >> i) & 1;
    for (int j = 0; j <= deg_Q; j++) {
      int q_j = (Q >> j) & 1;
      uint64_t coef = p_i & q_j;
      mul ^= coef << (i + j);
    }
  }
  return mul;
}

uint64_t poly_mul(uint32_t P, uint32_t Q) {
  uint64_t pol = 0;
  int deg_P = degree(P);
  for (uint32_t i = 0; i <= deg_P; i++)
    if ((P >> i) & 1)
      pol ^= (uint64_t)Q << i;

  return pol;
}

uint64_t poly_mod(uint64_t P, uint64_t Q) {
  int dp, dq;
  while ((dp = degree(P)) >= (dq = degree(Q))) {
    P ^= Q << (dp - dq);
  }
  return P;
}
