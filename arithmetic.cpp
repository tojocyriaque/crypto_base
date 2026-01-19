#include "arithmetic/arithmetic.hpp"
#include "bit_manip/bit_manip.hpp"

uint64_t poly_mul(uint32_t P, uint32_t Q) {
  uint64_t pol = 0;
  int deg_P = degree(P);
  for (uint32_t i = 0; i <= deg_P; i++)
    if ((P >> i) & 1)
      pol ^= (uint64_t)Q << i;

  return pol;
}

uint64_t poly_mod(uint64_t P, uint64_t Q) {
  int dp = degree(P), dq = degree(Q);
  while ((dp = degree(P)) >= dq) {
    P ^= Q << (dp - dq);
  }
  return P;
}

uint64_t poly_gcd(uint64_t P, uint64_t Q) {
  uint64_t R;
  while (Q > 0) {
    R = poly_mod(P, Q);
    P = Q;
    Q = R;
  }
  return P;
}