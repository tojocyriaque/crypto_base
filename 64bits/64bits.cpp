#include "bit_manip.hpp"
#include "arithmetic.hpp"

// BITS MANIPULATIONS

string binary(uint64_t n) {
  string bin = "";
  while (n > 0) {
    bin += (n % 2) + 48;
    n = n / 2;
  }
  return bin;
}

int count_1bit(uint64_t n) {
  int c1 = 0;
  while (n > 0) {
    c1 += n % 2;
    n = n >> 1;
  }
  return c1;
}

int degree(uint64_t n) {
  int deg = -1;
  while (n > 0) {
    deg++;
    n >>= 1;
  }
  return deg;
}

// POLYNOMIAL ARITHMETICS

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