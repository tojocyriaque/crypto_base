#include "headers/gf2poly.h"
/**
Arithmetic operations
*/
gf2poly gf2poly_mul(gf2poly P, gf2poly Q) {
  size_t dp = degree(P);
  gf2poly _Pol = 0;
  for (size_t k = 0; k <= dp; k++) {
    auto zero = ((P >> k) & gf2poly(1)) == gf2poly(0);
    if (!zero)
      _Pol = _Pol ^ (Q << k);
  }
  return _Pol;
}

gf2poly gf2poly_mod(gf2poly P, gf2poly Q) {
  size_t dp, dq = degree(Q);
  while ((dp = degree(P)) >= dq)
    P = P ^ (Q << (dp - dq));

  return P;
}

gf2poly gf2poly_gcd(gf2poly P, gf2poly Q) {
  gf2poly R = 0;
  while (!(Q == gf2poly(0))) {
    R = gf2poly_mod(P, Q);
    P = Q;
    Q = R;
  }
  return P;
}

gf2poly gf2poly_div(gf2poly P, gf2poly Q) {
  size_t dp = degree(P), dq = degree(Q);
  gf2poly quotient = 0;
  while ((dp = degree(P)) >= dq) {
    size_t shift = dp - dq;
    P = P ^ (Q << shift);
    quotient = quotient ^ (gf2poly(1) << shift);
  }
  return quotient;
}

gf2poly gf2poly_pow_mod(gf2poly a, uint64_t n, gf2poly m) {
  gf2poly res(1);
  a = a % m;
  while (n > 0) {
    if (n & 1)
      res = (res * a) % m;
    a = (a * a) % m;
    n >>= 1;
  }
  return res;
}