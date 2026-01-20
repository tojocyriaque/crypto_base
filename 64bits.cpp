#include "64bits/arithmetic.hpp"
#include "64bits/bit_manip.hpp"
#include "64bits/facto.hpp"
#include <cstdint>
#include <iostream>

// BITS MANIPULATIONS
string binary(uint64_t n) {
  string bin = "";
  while (n > 0) {
    bin = "01"[n % 2] + bin;
    n >>= 1;
  }
  return bin;
}

int count_1bit(uint64_t n) {
  int c1 = 0;
  while (c1 += n % 2 && n > 0)
    n >>= 1;
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
// END BIT MANIPS
// --------------------------------------------------------------

// POLYNOMIAL ARITHMETICS

uint64_t poly_mul(uint32_t P, uint32_t Q) {
  uint64_t pol = 0;
  int deg_P = degree(P);
  for (int i = 0; i <= deg_P; i++)
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
// END ARITHMETICS
// --------------------------------------------------------------

uint64_t poly_div(uint64_t P, uint64_t Q) {
  int dp = degree(P), dq = degree(Q);
  uint64_t quotient = 0;
  while ((dp = degree(P)) >= dq) {
    int shift = dp - dq;
    P ^= Q << shift;
    quotient ^= 1ULL << shift;
  }
  return quotient;
}

// FACTORISATIONS UTILS
// Naive factorisations of P in GF(2)(X)
void find_factorisation(uint64_t P) {
  for (uint64_t Q = 2; Q < P; Q++) {
    uint64_t R = poly_mod(P, Q);
    if (R == 0) {
      uint64_t G = poly_div(P, Q);
      cout << "(" << polynomial_exp(P) << ") | " << binary(P) << " | " << P
           << " = (" << polynomial_exp(G) << ")"
           << " * (" << polynomial_exp(Q) << ")"
           << " | " << "(" << binary(G) << ") * "
           << "(" << binary(Q) << ") "
           << " | " << "(" << G << ") * "
           << "(" << Q << ") " << endl;
    }
  }
}

// express an integer into it's polynomial representation in GF(2)(X)
string polynomial_exp(uint64_t P) {
  string pol = "";
  int p = 0;
  while (P > 0) {
    bool notnull = P % 2 == 1;
    if (notnull)
      pol = (p == 0 ? "1" : "x") + (p > 1 ? to_string(p) : "") + pol;

    p++;
    P >>= 1;
    if (P != 0 && notnull)
      pol = " + " + pol;
  }
  return pol;
}
// END FACTORISATIONS
// --------------------------------------------------------------
